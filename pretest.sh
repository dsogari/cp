#!/usr/bin/sh
cat $1/input.txt | build/release/$1 | diff - $1/output.txt
