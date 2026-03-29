#!/bin/bash
# 文件名: gdb_dump_all_threads.sh
# 用法: ./gdb_dump_all_threads.sh ./my_program arg1 arg2

# 获取程序和参数
PROG="$1"
shift
ARGS="$@"

# 输出日志文件名
LOGFILE="gdb_backtrace_$(date +%Y%m%d_%H%M%S).log"

echo "Running $PROG with args: $ARGS"
echo "GDB log will be saved to $LOGFILE"

# 使用 gdb 批处理模式运行程序，捕获所有线程调用栈
gdb --batch \
    --ex "run $ARGS" \
    --ex "thread apply all bt" \
    --ex "quit" \
    --args "$PROG" $ARGS &> "$LOGFILE"

echo "Done. Backtrace saved in $LOGFILE"