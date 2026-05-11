#!/bin/bash
if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <path>"
  exit 1
fi

p="$1"

if [[ ! -e "$p" ]]; then
  echo "Path not found"
  exit 2
elif [[ -L "$p" ]]; then
  ls -l "$p"
elif [[ -f "$p" && -r "$p" ]]; then
  mkdir -p /tmp/backup
  cp -p "$p" /tmp/backup
  echo "Copied $p to /tmp/backup"
elif [[ -d "$p" ]]; then
  echo "Directory backup is not supported yet"
else
  echo "unsupported path type"
fi
