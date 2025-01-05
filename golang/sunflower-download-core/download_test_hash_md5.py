import hashlib
import os
import sys

def calculate_md5(file_path: str, chunk_size: int = 8192) -> str:
    """
    计算文件的 MD5 哈希值
    """
    md5_hash = hashlib.md5()
    try:
        with open(file_path, "rb") as f:
            for chunk in iter(lambda: f.read(chunk_size), b""):
                md5_hash.update(chunk)
        return md5_hash.hexdigest()
    except Exception as e:
        print(f"计算文件 {file_path} 的 MD5 哈希值时出错: {e}")
        return None

def main():
    # 检查是否传入文件路径
    if len(sys.argv) < 2:
        print("请将文件或文件夹拖放到此脚本上，或通过命令行传递文件路径。")
        return

    # 获取文件或文件夹路径
    path = sys.argv[1]

    # 如果是文件
    if os.path.isfile(path):
        md5_hash = calculate_md5(path)
        if md5_hash:
            print(f"文件: {path}")
            print(f"MD5 哈希值: {md5_hash}")

    # 如果是文件夹
    elif os.path.isdir(path):
        for root, _, files in os.walk(path):
            for file in files:
                file_path = os.path.join(root, file)
                md5_hash = calculate_md5(file_path)
                if md5_hash:
                    print(f"文件: {file_path}")
                    print(f"MD5 哈希值: {md5_hash}")
                    print("-" * 50)
    else:
        print("路径无效，请输入文件或文件夹路径。")

if __name__ == "__main__":
    main()