#!/bin/bash
seq 1 50 > data.txt
cat data.txt > copy.txt
if [ $? -eq 0 ]; then echo "Copy successful"; fi
cat nonexistent.txt > /dev/null 2> errors.log
if [ -s errors.log ]; then
    echo "Errors found:"
    cat errors.log
fi
echo "DONE" >> data.txt
echo "Lines in data.txt: $(wc -l < data.txt)"
