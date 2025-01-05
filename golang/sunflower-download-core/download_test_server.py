from fastapi import FastAPI, Request, HTTPException
from fastapi.responses import StreamingResponse
from typing import Optional
import hashlib
import os
import uvicorn

app = FastAPI()

# 全局变量用于缓存文件数据和哈希值
cached_file_data: Optional[bytes] = None
cached_file_hash: Optional[str] = None

def generate_random_file(size: int) -> bytes:
    """生成指定大小的随机文件数据"""
    return os.urandom(size)

def calculate_file_hash(data: bytes) -> str:
    """计算文件的 MD5 哈希值"""
    md5_hash = hashlib.md5()
    md5_hash.update(data)
    return md5_hash.hexdigest()

@app.head("/download_test")
@app.head("/download_test/")
async def _(request: Request):
    """HEAD 请求：生成文件并返回文件大小和哈希值"""
    global cached_file_data, cached_file_hash

    # 生成一个 10MB 的随机文件
    file_size = 10 * 1024 * 1024  # 10 MB
    cached_file_data = generate_random_file(file_size)
    cached_file_hash = calculate_file_hash(cached_file_data)
    
    print("收到多线程文件下载 HEAD 请求hash MD5:", cached_file_hash, " size:", file_size)
    
    # 返回文件大小和哈希值
    headers = {
        "Content-Length": str(file_size),
        "X-File-Hash": cached_file_hash,
    }
    
    print(headers)
    
    return headers

@app.get("/download_test")
@app.get("/download_test/")
async def _(request: Request):
    """GET 请求：支持多线程下载"""
    global cached_file_data, cached_file_hash

    # 检查是否已经生成文件
    if cached_file_data is None:
        
        file_size = 10 * 1024 * 1024  # 10 MB
        cached_file_data = generate_random_file(file_size)
        cached_file_hash = calculate_file_hash(cached_file_data)
        
        print("收到多线程文件下载 GET 请求hash MD5:", cached_file_hash, " size:", file_size)

    # 获取 Range 头
    range_header = request.headers.get("Range")
    file_size = len(cached_file_data)

    if range_header:
        # 处理 Range 请求
        start, end = parse_range_header(range_header, file_size)
        chunk = cached_file_data[start:end + 1]
        headers = {
            "Content-Range": f"bytes {start}-{end}/{file_size}",
            "Content-Length": str(len(chunk)),
            "Accept-Ranges": "bytes",
        }
        return StreamingResponse(
            iter([chunk]),
            status_code=206,  # Partial Content
            headers=headers,
            media_type="application/octet-stream",
        )
    else:
        # 返回整个文件
        headers = {
            "Content-Length": str(file_size),
            "Accept-Ranges": "bytes",
            "X-File-Hash": cached_file_hash,
        }
        return StreamingResponse(
            iter([cached_file_data]),
            headers=headers,
            media_type="application/octet-stream",
        )

def parse_range_header(range_header: str, file_size: int) -> tuple[int, int]:
    """解析 Range 头并返回起始和结束字节位置"""
    if not range_header.startswith("bytes="):
        raise HTTPException(status_code=400, detail="Invalid Range header")

    range_values = range_header[6:].split("-")
    start = int(range_values[0])
    end = int(range_values[1]) if range_values[1] else file_size - 1

    if start >= file_size or end >= file_size or start > end:
        raise HTTPException(status_code=416, detail="Requested Range Not Satisfiable")

    return start, end

@app.on_event("shutdown")
def clear_cache():
    """清空缓存"""
    global cached_file_data, cached_file_hash
    cached_file_data = None
    cached_file_hash = None
    print("Cache cleared.")

if __name__ == "__main__":
    uvicorn.run(app, host=["0.0.0.0", "[::]"], port=80)