#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <PID>"
    exit 1
fi

PID=$1

# Check that the process exists
if ! kill -0 "$PID" 2>/dev/null; then
    echo "Error: process $PID does not exist."
    exit 1
fi

# Send SIGUSR1 five times
for i in $(seq 1 5); do
    echo "Sending SIGUSR1 ($i/5)..."
    kill -USR1 "$PID"
    sleep 1
done

# Send SIGUSR2 to print and reset the counter
echo "Sending SIGUSR2..."
kill -USR2 "$PID"

# Wait, then terminate
sleep 3
echo "Sending SIGTERM..."
kill -TERM "$PID"
# Wait for the process to terminate and collect exit status
wait "$PID"
echo "C program exited with status $?."
