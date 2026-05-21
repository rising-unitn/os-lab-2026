#!/bin/bash
dir="${1:-.}"
interval="${2:-2}"

[[ -d "$dir" ]] || { echo "Directory not found"; exit 1; }
[[ "$interval" =~ ^[0-9]+$ ]] || { echo "Interval must be an integer"; exit 1; }

declare -A snap

take_snapshot() {
  local p mtime
  local -n out_ref=$1
  out_ref=()
  for p in "$dir"/*; do
    [[ -e "$p" ]] || continue
    mtime=$(stat -f "%m" "$p" 2>/dev/null)
    out_ref["$p"]="$mtime"
  done
}

take_snapshot snap
trap 'echo; echo "Stopped."; exit 0' INT

while true; do
  sleep "$interval"
  declare -A current
  take_snapshot current

  created=0; modified=0; deleted=0

for p in "${!current[@]}"; do
  if [[ -z "${snap[$p]+x}" ]]; then
    ((created++))
    echo "NEW: $p"
  elif [[ "${current[$p]}" != "${snap[$p]}" ]]; then
    ((modified++))
    echo "MODIFIED: $p"
  fi
done

for p in "${!snap[@]}"; do
    if [[ -z "${current[$p]+x}" ]]; then
      ((deleted++))
      echo "DELETED: $p"
    fi
  done
  echo "Summary -> created=$created modified=$modified deleted=$deleted"
  snap=()
  for p in "${!current[@]}"; do
    snap["$p"]="${current[$p]}"
  done
done
