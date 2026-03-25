#!/bin/bash
set -e  # 如果任何命令失败，立即退出

echo "===== Running game.exe tests ====="

echo
echo "Test 1: Move north then attack"
./game.exe <<EOF
n
a
EOF

echo
echo "Test 2: Explore all directions"
./game.exe <<EOF
n
e
w
s
m
EOF

echo
echo "Test 3: Look command"
./game.exe <<EOF
l
EOF

echo
echo "Test 4: Attack without monster"
./game.exe <<EOF
a
EOF

echo
echo "Test 5: Invalid command"
./game.exe <<EOF
x
EOF

echo
echo "All tests finished."