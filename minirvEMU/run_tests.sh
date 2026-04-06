#! /usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

TEST_NAME="${1:-test1}"
BIN_FILE="${2:-}"
CYCLES="${3:-20}"

if [[ ! -d tests ]]; then
  echo "tests directory not found"
  exit 1
fi

mapfile -t TEST_LIST < <(
  grep -hE '^[[:space:]]*void[[:space:]]+test[[:alnum:]_]*[[:space:]]*\(' tests/*.c \
    | sed -E 's/^[[:space:]]*void[[:space:]]+(test[[:alnum:]_]*)[[:space:]]*\(.*/\1/' \
    | sort -u
)

if [[ "${#TEST_LIST[@]}" -eq 0 ]]; then
  echo "No test functions found in tests/*.c"
  exit 1
fi

if [[ "$TEST_NAME" == "-l" ]]; then
  printf '%s\n' "${TEST_LIST[@]}"
  exit 0
fi

if [[ "$TEST_NAME" == "-h" ]]; then
  echo "Usage: $0 [test_name|--list] [file.bin] [cycles]"
  exit 0
fi

FOUND=0
for t in "${TEST_LIST[@]}"; do
  if [[ "$t" == "$TEST_NAME" ]]; then
    FOUND=1
    break
  fi
done

if [[ "$FOUND" -ne 1 ]]; then
  echo "Unknown test: $TEST_NAME"
  echo "Available tests:"
  printf '  %s\n' "${TEST_LIST[@]}"
  echo "Usage: ./run_tests.sh [test_name|--list] [file.bin] [cycles]"
  exit 1
fi

make build/libminirvEMU.so



# shellcheck disable=SC2016
gcc -g -Wall -I. -Iinclude -o build/minirv_test_runner tests/tests_runner/minirv_test_runner.c tests/*.c -Lbuild -lminirvEMU -Wl,-rpath,'$ORIGIN'
./build/minirv_test_runner "$TEST_NAME" "$BIN_FILE" "$CYCLES"