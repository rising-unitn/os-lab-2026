#!/bin/bash
[[ $# -eq 1 ]] || { echo "Usage: $0 <path>"; exit 1; }
p="$1"
[[ -e "$p" ]] || { echo "missing"; exit 2; }
[[ -f "$p" ]] && echo "type: file"
[[ -d "$p" ]] && echo "type: directory"
[[ -L "$p" ]] && echo "type: symlink"
ls -ld "$p"
