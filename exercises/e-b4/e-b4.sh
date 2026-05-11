#!/bin/bash
if [[ -r /etc/passwd ]]; then
  echo "/etc/passwd is readable"
  echo -n "total users: "
  cat /etc/passwd | wc -l
  echo "first 5 entries:"
  head -n 5 /etc/passwd
else
  echo "/etc/passwd is not readable"
  exit 1
fi
