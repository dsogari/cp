#!/usr/bin/sh
IFS='/' read -r judge contest problem <<EOF
$1
EOF
"build/debug/$judge/$contest/${judge}_${contest}_${problem}" | diff -Z - "$1/output"
