#!/bin/bash
fifo="/tmp/z16_fifo_$$"   # $$ makes the name unique per run
mkfifo "$fifo"

cleanup() { rm -f "$fifo"; }
trap cleanup EXIT
# Consumer: reads lines until EOF or SIGTERM closes the read end
( while IFS= read -r line; do
    echo "consumer got: $line"
  done < "$fifo"
  echo "consumer: FIFO closed, exiting"
) &
consumer_pid=$!

# Producer: writes 5 messages then exits (EOF on consumer's read end)
( for i in 1 2 3 4 5; do
    echo "msg-$i"
    sleep 0.5
  done > "$fifo"
) &
producer_pid=$!

wait "$producer_pid"                       # wait for producer to finish
kill -TERM "$consumer_pid" 2>/dev/null     # signal consumer to stop
wait "$consumer_pid" 2>/dev/null
echo "all done"
