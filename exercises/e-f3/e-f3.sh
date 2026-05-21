#!/bin/bash
dir="${1:-.}"
for f in "$dir"/*.txt; do
  [[ -f "$f" ]] || continue
  mv "$f" "$f.bak"
  echo "renamed: $f -> $f.bak"
done
