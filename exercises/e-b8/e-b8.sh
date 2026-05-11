#!/bin/bash
if [[ $# -ne 2 ]]; then
  echo "Usage: $0 <path1> <path2>"
  exit 1
fi
a="$1"; b="$2"
[[ -e "$a" && -e "$b" ]] || { echo "missing input path"; exit 2; }

if [[ -d "$a" && -d "$b" ]]; then
  echo "contents of $a:"
  ls "$a"
  echo "contents of $b:"
  ls "$b"

elif [[ -f "$a" && -f "$b" ]]; then
  echo "$a:"
  wc -c "$a"
  echo "$b:"
  wc -c "$b"

else
  echo "incompatible types"
fi
