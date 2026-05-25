#!/bin/bash
WORKER_BIN="/tmp/e-z19-worker"
gcc code/exercises/e-z19/e-z19-worker.c -o "$WORKER_BIN" || exit 1

declare -a pids=()   # array tracking all live worker PIDs

start_worker() {
  "$WORKER_BIN" &    # launch worker in background
  pids+=("$!")       # record its PID
  echo "Started worker PID=${pids[-1]}"
}

stop_all() {
  for p in "${pids[@]}"; do
    kill -TERM "$p" 2>/dev/null
  done
  echo "All workers terminated"
}

# On SIGINT or SIGTERM: kill all workers, then exit supervisor
trap 'stop_all; exit 0' INT TERM

# Launch the initial pool of two workers
start_worker
start_worker

while true; do
  # Walk all tracked PIDs; restart any that have died
  for i in "${!pids[@]}"; do
    p="${pids[$i]}"
    if ! kill -0 "$p" 2>/dev/null; then
      echo "Worker $p exited — restarting"
      unset 'pids[$i]'   # remove the stale entry
      start_worker        # adds fresh PID to pids[]
    fi
  done
  sleep 1
done
