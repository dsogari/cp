#!/usr/bin/sh
cat contest/$1/$2/input.txt | build/debug/contest/$1/$1_$2 | diff - contest/$1/$2/output.txt
