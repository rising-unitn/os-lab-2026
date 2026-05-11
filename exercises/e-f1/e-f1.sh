#!/bin/bash
echo "before: $PWD"
( cd /tmp && echo "inside subshell: $PWD" )
echo "after: $PWD"
