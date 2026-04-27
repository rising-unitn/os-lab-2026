#!/bin/bash
gcc -o e-i4 e-i4.c
./e-i4 nonexistent.txt > /dev/null 2> errors.log
if [ $? -ne 0 ]; then
    echo "FAIL (expected): $(cat errors.log)"
fi
echo "test content" > existing.txt
./e-i4 existing.txt > /dev/null 2> errors.log
if [ $? -eq 0 ]; then
    echo "OK (expected): command succeeded"
fi
