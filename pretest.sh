#!/usr/bin/sh
cat $1/input.txt | build/debug/$1 | diff - $1/output.txt
