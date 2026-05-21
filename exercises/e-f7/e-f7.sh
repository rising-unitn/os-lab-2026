#!/bin/bash
count_exec() {
  local count=0
  for f in "$1"/*; do
    [[ -f "$f" && -x "$f" ]] && ((count++))
  done
  echo "$count"
  # (Alternatively, investigate 'grep' or 'awk' for a shorter solution!)
}

show_top() {
  ls -la "$1" | head -n "$2"
}
dir="${1:-.}"; n="${2:-5}"

echo "exec files: $(count_exec "$dir")"
show_top "$dir" "$n"
