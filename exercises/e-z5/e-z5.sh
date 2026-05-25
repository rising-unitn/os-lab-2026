#!/bin/bash
file="$1"
[[ -f "$file" ]] || { echo "Error: File not found!"; exit 1; }
echo "Lines: $(wc -l < "$file")"
echo "Words: $(wc -w < "$file")"
echo "Characters: $(wc -m < "$file")"
tr -s '[:space:]' '\n' < "$file" | tr '[:upper:]' '[:lower:]' | grep -v '^$' | sort | uniq -c | sort -rn | head -10
