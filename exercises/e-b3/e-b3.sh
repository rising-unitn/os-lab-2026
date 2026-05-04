#!/bin/bash
echo "hello links" > original.txt
ln original.txt hard.txt
ln -s original.txt soft.txt
rm original.txt
echo "hard link content:"; cat hard.txt
echo "soft link content:"; cat soft.txt 2>/dev/null || echo "broken symlink"
echo "Hard links keep inode data alive; symlinks need a valid target path."
