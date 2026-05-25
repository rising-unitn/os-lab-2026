#!/bin/bash

# Temporary workspace — always cleaned up on exit
tmpdir=$(mktemp -d)
logfile="$tmpdir/signal.log"

cleanup() {
  # Called automatically on EXIT, even after a signal handler returns
  [[ -d "$tmpdir" ]] && rm -rf "$tmpdir" && echo "Cleaned up $tmpdir"
}

on_int() {
  # Ctrl-C sends SIGINT (signal 2); exit code 128+2 = 130 by convention
  echo "INT received at $(date)" | tee -a "$logfile"
  exit 130
}

on_term() {
  # `kill <pid>` sends SIGTERM (signal 15); exit code 128+15 = 143
  echo "TERM received at $(date)" | tee -a "$logfile"
  exit 143
}

# Register handlers BEFORE entering the loop
trap on_int  INT
trap on_term TERM
trap cleanup EXIT    # EXIT fires last, after on_int/on_term return

echo "Running. PID=$$ — send SIGINT (Ctrl-C) or: kill -TERM $$"
while true; do
  echo "tick $(date '+%T')" | tee -a "$logfile"
  sleep 1
done
