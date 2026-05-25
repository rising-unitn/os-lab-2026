#!/bin/bash

tasks_file="tasks.txt"
touch "$tasks_file"

show_help() {
  echo "Usage: $0 {add \"task\"|list|done N|remove N|clear|help}"
}

case "$1" in
  add)
    shift
    [[ -n "$*" ]] || { echo "Missing task description"; exit 1; }
    echo "$*" >> "$tasks_file"
    ;;
  list)
    nl -w2 -s'. ' "$tasks_file"
    ;;
  done)
    [[ "$2" =~ ^[0-9]+$ ]] || { echo "Invalid line"; exit 1; }
    sed -i '' "${2}s/^/[DONE] /" "$tasks_file"
    ;;

remove)
    [[ "$2" =~ ^[0-9]+$ ]] || { echo "Invalid line"; exit 1; }
    sed -i '' "${2}d" "$tasks_file"
    ;;
  clear)
    : > "$tasks_file"
    ;;
  help|"")
    show_help
    ;;
  *)
    show_help
    exit 1
    ;;
esac
