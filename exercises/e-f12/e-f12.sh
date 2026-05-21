#!/bin/bash

[[ -d /tmp/backup ]] || mkdir -p /tmp/backup

cd /etc || exit 1

for file in *; do
  if [[ -f "$file" && -r "$file" ]]; then
    if [[ -f /tmp/backup/$file ]]; then
      echo "Overwriting $file"
    fi
    cp -p "$file" /tmp/backup
    echo "Copied $file"
  fi
done
