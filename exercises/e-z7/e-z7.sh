#!/bin/bash
backup_home() {
  archive="/tmp/backup-$(whoami)-$(date +%Y%m%d-%H%M%S).tar.gz"
  tar czf "$archive" "$HOME"
  echo "Backup created: $archive"
}

while true; do
  echo "1) Disk usage"
  echo "2) Top CPU processes"
  echo "3) Uptime"
  echo "4) Backup home"
  echo "5) Exit"

read -r choice
  case "$choice" in
    1) df -h ;;
    2) ps -eo pid,comm,%cpu --sort=-%cpu | head -n 10 ;;
    3) uptime ;;
    4) backup_home ;;
    5) break ;;
    *) echo "Invalid option" ;;
  esac
done
