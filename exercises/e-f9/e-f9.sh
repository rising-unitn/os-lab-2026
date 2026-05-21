#!/bin/bash
logfile="${1:-logfile.txt}"
[[ -f "$logfile" ]] || { echo "Error: file not found"; exit 1; }

error_count=0
warning_count=0
info_count=0

while IFS= read -r line; do
  case "$line" in
    ERROR*) ((error_count++)) ;;
    WARNING*) ((warning_count++)) ;;
    INFORMATION*) ((info_count++)) ;;
  esac
done < "$logfile"

echo "ERROR=$error_count WARNING=$warning_count INFORMATION=$info_count"

if (( error_count > 3 || warning_count > 5 )); then
  echo "Warning: excessive ERROR/WARNING lines"
fi
