#!/bin/bash

find /home/g_i_m -name $1 -perm $2 2>&1 | grep -v "Permission denied" > in.txt
