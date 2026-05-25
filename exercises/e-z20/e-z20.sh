#!/bin/bash

PID_FILE="/tmp/z20.pid"
LOG_FILE="/tmp/z20.log"
STATE_FILE="/tmp/z20.state"

start_service() {
  if [[ -f "$PID_FILE" ]] && kill -0 "$(cat "$PID_FILE")" 2>/dev/null; then
    echo "Service already running (PID=$(cat "$PID_FILE"))"; return 1
  fi
  # Launch background subshell — acts as the service daemon

(
    trap 'echo "stopped" > "$STATE_FILE"; exit 0' TERM INT
    echo "running" > "$STATE_FILE"
    while true; do
      echo "heartbeat $(date '+%Y-%m-%dT%H:%M:%S')" >> "$LOG_FILE"
      sleep 1
    done
  ) &
  echo $! > "$PID_FILE"
  echo "Service started (PID=$!)"
}

stop_service() {
  [[ -f "$PID_FILE" ]] || { echo "Not running (no PID file)"; return 1; }
  local pid; pid=$(cat "$PID_FILE")
  kill -TERM "$pid" 2>/dev/null && echo "Sent SIGTERM to PID $pid"
  rm -f "$PID_FILE"
}

status_service() {
  if [[ -f "$PID_FILE" ]] && kill -0 "$(cat "$PID_FILE")" 2>/dev/null; then
    echo "Status: RUNNING (PID=$(cat "$PID_FILE"))"
  else
    echo "Status: STOPPED"
  fi
  [[ -f "$STATE_FILE" ]] && echo "State file: $(cat "$STATE_FILE")"
  [[ -f "$LOG_FILE"   ]] && echo "Last log:   $(tail -1 "$LOG_FILE")"
}

case "$1" in
  start)  start_service  ;;
  stop)   stop_service   ;;
  status) status_service ;;
  *)      echo "Usage: $0 {start|stop|status}"; exit 1 ;;
esac
