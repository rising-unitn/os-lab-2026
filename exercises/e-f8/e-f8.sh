#!/bin/bash
stats() {
  local files=0 dirs=0
  for f in "$1"/*; do
    [[ -f "$f" ]] && ((files++))
    [[ -d "$f" ]] && ((dirs++))
  done
  echo "files=$files dirs=$dirs"
}

largest() {
  local max_f="" max_s=0 size
  for f in "$1"/*; do
    if [[ -f "$f" ]]; then
      size=$(wc -c < "$f")
      if (( size > max_s )); then
        max_s=$size; max_f=$f
      fi
    fi
  done
  echo "$max_s bytes: $max_f"
}

case "$1" in
  stats)
    stats "${2:-.}"
    ;;
  largest)
    largest "${2:-.}"
    ;;
  help|"")
    echo "Usage: $0 {stats|largest} [dir]"
    ;;
  *) echo "Unknown command"; exit 1 ;;
esac
