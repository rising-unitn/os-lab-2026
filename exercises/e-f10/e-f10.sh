#!/bin/bash
count=0
walk() {
  local dir="$1"
  for entry in "$dir"/*; do
    [[ -e "$entry" ]] || continue
    printf '%s\n' "$entry"
    ((count++))
    [[ -d "$entry" && ! -L "$entry" ]] && walk "$entry"
  done
}

root="${1:-.}"
walk "$root"
echo "total=$count"
