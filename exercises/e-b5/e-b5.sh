#!/bin/bash
echo "sudo groupadd labgrp"
echo "sudo useradd -m -g labgrp -s /bin/bash labuser"
echo "sudo usermod -aG sudo labuser"
echo "sudo passwd labuser"
