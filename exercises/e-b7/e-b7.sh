#!/bin/bash
mkdir -p permtest
touch permtest/world.txt permtest/ownerx.sh permtest/ownerwx.sh

chmod o+w permtest/world.txt
chmod u+x permtest/ownerx.sh
chmod u+wx permtest/ownerwx.sh

ls -l permtest/world.txt permtest/ownerx.sh permtest/ownerwx.sh
