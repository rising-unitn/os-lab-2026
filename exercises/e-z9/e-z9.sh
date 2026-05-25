#!/bin/bash

file="$1"
[[ -r "$file" ]] || { echo "Error: file not readable"; exit 1; }

tmp_words=$(mktemp)
trap 'rm -f "$tmp_words"' EXIT

tr '[:upper:]' '[:lower:]' < "$file" | tr -cs '[:alpha:]' '\n' | grep -v '^$' > "$tmp_words"

unique_count=$(sort "$tmp_words" | uniq | wc -l)
echo "Unique words: $unique_count"
echo "Top 5 words:"
sort "$tmp_words" | uniq -c | sort -rn | head -n 5

short=$(awk 'length($0)<=3 {c++} END {print c+0}' "$tmp_words")
medium=$(awk 'length($0)>=4 && length($0)<=6 {c++} END {print c+0}' "$tmp_words")
long=$(awk 'length($0)>=7 {c++} END {print c+0}' "$tmp_words")

total_len=$(awk '{s+=length($0)} END {print s+0}' "$tmp_words")
total_words=$(wc -l < "$tmp_words")
avg=$(awk -v s="$total_len" -v n="$total_words" 'BEGIN { if (n==0) print "0.00"; else printf "%.2f", s/n }')

echo "Average word length: $avg"
echo "short: $(printf '%*s' "$short" '' | tr ' ' '*')"
echo "medium: $(printf '%*s' "$medium" '' | tr ' ' '*')"
echo "long: $(printf '%*s' "$long" '' | tr ' ' '*')"
