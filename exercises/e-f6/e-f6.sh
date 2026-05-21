#!/bin/bash
if [[ $# -eq 3 ]]; then
  a="$1"; op="$2"; b="$3"
else
  echo "Usage: $0 <n1> <op> <n2>"
  exit 1
fi

case "$op" in
  +) echo $((a + b)) ;;
  -) echo $((a - b)) ;;
  \*) echo $((a * b)) ;;
  /) [[ "$b" -eq 0 ]] && echo "division by zero" || echo $((a / b)) ;;
  *) echo "invalid operator"; exit 2 ;;
esac
