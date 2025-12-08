#!/bin/bash

g++ -std=c++17 -O2 -o pager src/main.cpp

if [ $? -ne 0 ]; then
  echo "Compilation failed"
  exit 1
fi

echo "Running tests..."

run_test() {
  algo=$1
  frames=$2
  input=$3

  echo "Test: $algo, frames=$frames, input=$input"

  ./pager --algo=$algo --frames=$frames --input=$input > out.txt

  if grep -q "Page faults" out.txt; then
    echo "PASS"
  else
    echo "FAIL"
    exit 1
  fi
}

run_test FIFO 4 tests/trace1.txt
run_test SC   4 tests/trace1.txt
run_test CLOCK 4 tests/trace1.txt
run_test AGING 4 tests/trace1.txt
run_test OPT   4 tests/trace1.txt

echo "All tests passed."
exit 0
