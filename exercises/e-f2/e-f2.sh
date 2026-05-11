#!/bin/bash
dir="${1:-.}"
files=0; dirs=0; sh=0
for file in "$dir"/*; do
  [[ -f "$file" ]] && files=$((files + 1))
  [[ -d "$file" ]] && dirs=$((dirs + 1))
  [[ -f "$file" && "$file" == *.sh ]] && ((sh++))
done
echo "files=$files dirs=$dirs sh=$sh"
