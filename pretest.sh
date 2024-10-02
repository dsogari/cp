#!/usr/bin/sh
build/debug/codeforces/$1/$1_$2 | diff - codeforces/$1/$2/output
