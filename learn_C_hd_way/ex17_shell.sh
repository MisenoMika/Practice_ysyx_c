#!/bin/bash
set -e  # 如果任何命令失败，立即退出

DBFILE="ex17.dat"

# 1. 创建数据库
echo "Creating database..."
./ex17.exe $DBFILE c 512 128

# 2. 插入几条数据
echo "Setting records..."
./ex17.exe $DBFILE s 0 Alice alice@example.com
./ex17.exe $DBFILE s 1 Bob bob@example.com
./ex17.exe $DBFILE s 2 Charlie charlie@example.com

# 3. 获取并打印记录
echo "Getting records..."
./ex17.exe $DBFILE g 0
./ex17.exe $DBFILE g 1
./ex17.exe $DBFILE g 2

# 4. 删除某条记录
echo "Deleting record 1..."
./ex17.exe $DBFILE d 1

# 5. 列出所有已设置的记录
echo "Listing all records..."
./ex17.exe $DBFILE l

# 6. 测试覆盖错误情况（可选）
# echo "Trying to get deleted record..."
# ./ex17.exe $DBFILE g 1  # 这应该触发错误并退出

echo "All tests passed!"