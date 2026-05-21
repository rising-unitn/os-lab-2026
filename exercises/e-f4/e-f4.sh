#!/bin/bash
if [[ $# -eq 1 ]]; then
  file="$1"
else
  echo "Usage: $0 <file>"
  exit 1
fi
empty=0;
comments=0;
other=0

while IFS= read -r line; do
  if [[ -z "$line" ]]; then
    ((empty++))
  elif [[ "$line" == \#* ]]; then
    ((comments++))
  else
    ((other++))
  fi
done < "$file"
echo "empty=$empty comments=$comments other=$other"
