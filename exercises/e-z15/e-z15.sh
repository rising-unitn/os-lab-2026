#!/bin/bash
set -o pipefail   # make $? reflect failures anywhere in a pipeline
run_pipeline() {
  local cmd="$1"
  echo "--- Running: $cmd"
  eval "$cmd"     # execute the pipeline
  local rc=$?
  # Capture PIPESTATUS immediately — it is wiped by the next command
  local -a statuses=("${PIPESTATUS[@]}")
  echo "Overall exit code: $rc"
  local i=0
  for s in "${statuses[@]}"; do
    echo "  stage[$i] exit code: $s"
    i=$(( i + 1 ))
  done
  echo ""
}

run_pipeline "seq 1 100 | grep 5 | wc -l"
run_pipeline "cat missing.txt | sort | uniq"
