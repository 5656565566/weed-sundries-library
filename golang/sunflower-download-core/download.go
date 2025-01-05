package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"io"
	"net/http"
	"net/url"
	"os"
	"path"
	"strconv"
	"strings"
	"sync"
	"time"
)

type MyError struct {
	code int64
	msg  string
}

// 实现 error 接口的 Error 方法
func (e MyError) Error() string {
	return fmt.Sprintf("Error: [%d] %s", e.code, e.msg)
}

// 分片下载器
type Downloader struct {
	url        string
	fileName   string
	ua         string
	threads    int
	chunkSize  int64
	totalSize  int64
	mu         sync.RWMutex
	downloaded int64
	speed      int64
	maxRetries int
	timeout    time.Duration
	status     int
	progress   []int64
}

const (
	downloading int = 1
	pausing     int = 2
	stopped     int = 3
)

func NewDownloader(url, fileName, ua string, threads int, chunkSize int64, maxRetries int, timeout time.Duration, totalSize int64) *Downloader {
	chunkNum := totalSize / chunkSize
	if totalSize%chunkSize != 0 {
		chunkNum++
	}
	return &Downloader{
		url:        url,
		fileName:   fileName,
		ua:         ua,
		threads:    threads,
		chunkSize:  chunkSize,
		maxRetries: maxRetries,
		timeout:    timeout,
		totalSize:  totalSize,
		status:     downloading,
		progress:   make([]int64, chunkNum), // 初始化进度信息
	}
}

func (d *Downloader) getFileSize() error {
	// 获取文件总大小
	resp, err := http.Get(d.url)
	if err != nil {
		return err
	}
	defer resp.Body.Close()

	if d.totalSize == -1 {
		d.totalSize, err = strconv.ParseInt(resp.Header.Get("Content-Length"), 10, 64)
		fmt.Printf("File size: %d \n", d.totalSize)
		if err != nil {
			return err
		}
	}

	return nil
}

// 加载下载信息
func (d *Downloader) loadProgress() error {
	file, err := os.Open(d.fileName)
	if err != nil {
		if os.IsNotExist(err) {
			return nil // 文件不存在，无需加载进度
		}
		return err
	}
	defer file.Close()

	// 获取文件大小
	fileInfo, err := file.Stat()
	if err != nil {
		return err
	}
	fileSize := fileInfo.Size()

	// 如果文件大小小于总大小，说明没有下载信息
	if fileSize <= d.totalSize {
		return nil
	}

	// 计算下载信息的起始位置
	infoSize := fileSize - d.totalSize

	infoData := make([]byte, infoSize)
	if _, err := file.ReadAt(infoData, d.totalSize); err != nil {
		return err
	}

	// 解码下载信息
	buf := bytes.NewReader(infoData)
	if err := binary.Read(buf, binary.LittleEndian, &d.chunkSize); err != nil {
		return err
	}
	if err := binary.Read(buf, binary.LittleEndian, &d.totalSize); err != nil {
		return err
	}
	if err := binary.Read(buf, binary.LittleEndian, &d.downloaded); err != nil {
		return err
	}
	for i := range d.progress {
		if err := binary.Read(buf, binary.LittleEndian, &d.progress[i]); err != nil {
			return err
		}
	}

	return nil
}

// 保存下载信息
func (d *Downloader) saveProgress() error {
	file, err := os.OpenFile(d.fileName, os.O_WRONLY|os.O_APPEND, 0644)
	if err != nil {
		return err
	}
	defer file.Close()

	// 编码下载信息
	buf := new(bytes.Buffer)
	if err := binary.Write(buf, binary.LittleEndian, d.chunkSize); err != nil {
		return err
	}
	if err := binary.Write(buf, binary.LittleEndian, d.totalSize); err != nil {
		return err
	}
	if err := binary.Write(buf, binary.LittleEndian, d.downloaded); err != nil {
		return err
	}
	for _, p := range d.progress {
		if err := binary.Write(buf, binary.LittleEndian, p); err != nil {
			return err
		}
	}

	// 写入文件
	if _, err := file.Write(buf.Bytes()); err != nil {
		return err
	}

	return nil
}

func (d *Downloader) finalizeFile() error {
	file, err := os.OpenFile(d.fileName, os.O_RDWR, 0644)
	if err != nil {
		return err
	}
	defer file.Close()

	// 截断文件以删除下载信息
	if err := file.Truncate(d.totalSize); err != nil {
		return err
	}

	return nil
}

func (d *Downloader) Download() error {

	// 获取文件大小
	if err := d.getFileSize(); err != nil {
		return err
	}

	// 加载下载信息
	if err := d.loadProgress(); err != nil {
		return err
	}

	// 创建或打开文件
	file, err := os.OpenFile(d.fileName, os.O_CREATE|os.O_RDWR, 0644)
	if err != nil {
		return err
	}
	defer file.Close()

	// 初始化文件大小
	if err := file.Truncate(d.totalSize); err != nil {
		return err
	}

	var wg sync.WaitGroup
	chunkNum := d.totalSize / d.chunkSize
	if d.totalSize%d.chunkSize != 0 {
		chunkNum++
	}

	// 启动显示进度和速度的 goroutine
	go d.showProgress()

	// 定期保存下载信息
	go func() {
		for {
			time.Sleep(1 * time.Second)
			if err := d.saveProgress(); err != nil {
				fmt.Printf("保存下载信息失败: %v\n", err)
			}
		}
	}()

	// 多线程下载
	chunkChan := make(chan int64, d.threads)
	errChan := make(chan error, d.threads) // 错误通道

	for i := 0; i < d.threads; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for chunkIndex := range chunkChan {
				if d.status == pausing {
					time.Sleep(1000)
					return
				}

				if d.status == stopped {
					errChan <- MyError{code: 56, msg: "下载已被用户取消"}
					return
				}

				if err := d.downloadChunk(chunkIndex); err != nil {
					errChan <- err
					return
				}
			}
		}()
	}

	for i := int64(0); i < chunkNum; i++ {
		chunkChan <- i
	}
	close(chunkChan)

	wg.Wait()

	// 检查是否有错误
	select {
	case err := <-errChan:
		return err
	default:
		// 下载完成后，检查文件大小并截断
		if err := d.finalizeFile(); err != nil {
			return err
		}
		return nil
	}
}

func (d *Downloader) downloadChunk(chunkIndex int64) error {
	if d.status == stopped {
		return nil
	}

	start := chunkIndex * d.chunkSize
	end := start + d.chunkSize - 1
	if end >= d.totalSize {
		end = d.totalSize - 1
	}

	for retry := 0; retry < d.maxRetries; retry++ {
		req, err := http.NewRequest("GET", d.url, nil)
		if err != nil {
			return err
		}
		req.Header.Set("User-Agent", d.ua)
		req.Header.Set("Range", fmt.Sprintf("bytes=%d-%d", start, end))

		client := &http.Client{
			Timeout: d.timeout,
		}
		resp, err := client.Do(req)
		if err != nil {
			fmt.Printf("Chunk %d download error: %v. Retrying (%d/%d)...\n", chunkIndex, err, retry+1, d.maxRetries)
			continue
		}
		defer resp.Body.Close()

		// 检查是否超出范围
		if resp.StatusCode == http.StatusRequestedRangeNotSatisfiable {
			fmt.Printf("Chunk %d 超出文件范围，停止下载\n", chunkIndex)
			d.status = stopped
			return nil
		}

		if resp.StatusCode != http.StatusPartialContent {
			fmt.Printf("Unexpected status code: %d\n", resp.StatusCode)
			continue
		}

		// 打开文件并移动指针到正确位置
		file, err := os.OpenFile(d.fileName, os.O_WRONLY, 0644)
		if err != nil {
			return err
		}
		defer file.Close()

		if _, err := file.Seek(start, io.SeekStart); err != nil {
			return err
		}

		// 写入文件
		n, err := io.Copy(file, resp.Body)
		if err != nil {
			fmt.Printf("Chunk %d write error: %v. Retrying (%d/%d)...\n", chunkIndex, err, retry+1, d.maxRetries)
			continue
		}

		if n != end-start+1 {
			fmt.Printf("Chunk %d size mismatch. Expected %d bytes, got %d bytes. Retrying (%d/%d)...\n", chunkIndex, end-start+1, n, retry+1, d.maxRetries)
			continue
		}

		// 更新下载进度
		d.mu.Lock()
		d.downloaded += n
		d.speed += n
		d.mu.Unlock()

		return nil
	}

	return fmt.Errorf("chunk %d failed to download after %d attempts", chunkIndex, d.maxRetries)
}

func (d *Downloader) showProgress() {
	startTime := time.Now()
	for {
		time.Sleep(1 * time.Second)

		d.mu.Lock()
		progress := float64(d.downloaded) / float64(d.totalSize) * 100
		speed := float64(d.speed) / 1024 / 1024 // 转换为 MB/s
		d.speed = 0                             // 重置速度计数器
		d.mu.Unlock()

		if d.status == stopped {
			fmt.Println("下载已取消")
			break
		}

		if progress > 100 { // 不然它可以给我下载到 127% ..
			progress = 100
		}

		elapsed := time.Since(startTime).Seconds()
		if elapsed > 0 {
			fmt.Printf("下载进度: %.2f%%, 下载速度: %.2f MB/s\n", progress, speed)
		}
	}
}

func getFileNameFromURL(downloadURL string) (string, error) {
	parsedURL, err := url.Parse(downloadURL)
	if err != nil {
		return "", err
	}
	return path.Base(parsedURL.Path), nil
}


func main() {
	url := flag.String("url", "", "下载文件的URL")
	fileName := flag.String("fileName", "", "保存文件的名称")
	ua := flag.String("ua", "", "用户代理字符串")
	threads := flag.Int("threads", 8, "下载线程数")
	totalSize := flag.Int64("totalSize", -1, "文件大小（一般情况无需附加参数）")
	chunkSize := flag.Int64("chunkSize", 1024*1024, "每个下载块的大小 (字节) min : 32767")
	maxRetries := flag.Int("maxRetries", 3, "最大重试次数")
	timeout := flag.Duration("timeout", 30*time.Second, "下载超时时间")
	port := flag.Int("port", 0, "启动的端口，附带此项不可以使用控制行下载")
	help := flag.Bool("help", false, "帮助信息")
	version := flag.Bool("v", false, "版本号")

	flag.Parse()

	if *version {
		fmt.Println("1.0.4")
		fmt.Println("@5656565566")
		return
	}

	if *port > 0 {
		fmt.Println("还不支持")
		return
	}

	if len(flag.Args()) > 0 {
		*url = flag.Args()[0]
	}

	if *help {
		flag.PrintDefaults()
		return
	}

	if *url == "" {
		fmt.Println("必须提供下载文件的URL")
		return
	}

	if *chunkSize < 32767 {
		fmt.Println("分片太小")
		return
	}

	if *threads > 128 {
		fmt.Println("下载线程不能超过 128 个")
		return
	}

	if *fileName == "" {
		var err error
		*fileName, err = getFileNameFromURL(*url)
		if err != nil {
			fmt.Println("无法从URL获取文件名:", err)
			return
		}
	}

	downloader := NewDownloader(*url, *fileName, *ua, *threads, *chunkSize, *maxRetries, *timeout, *totalSize)
	err := downloader.Download()

	if err != nil {
		fmt.Println("下载出错:", err)
	} else {
		fmt.Println("下载完成")
	}
}
