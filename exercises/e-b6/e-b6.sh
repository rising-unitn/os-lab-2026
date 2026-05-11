#!/bin/bash
if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <file>"
  exit 1
fi
f="$1"
if [[ ! -r "$f" ]]; then
  echo "File not readable"
  exit 2
fi

echo "lines words chars:"
wc "$f"
echo "lines 4-7:"
head -n 7 "$f" | tail -n 4
