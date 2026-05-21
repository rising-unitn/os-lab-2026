#!/bin/bash
if [[ $# -eq 1 ]]; then
  file="$1"
else
  echo "Usage: $0 <file>"
  exit 1
fi

tries=0
until [[ -e "$file" || $tries -ge 5 ]]; do
  ((tries++))
  echo "attempt $tries: not found"
  sleep 1
done
[[ -e "$file" ]] && echo "file appeared" || echo "timeout"
