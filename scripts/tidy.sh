#!/bin/sh
for f in $PWD/../*.cpp
do
    echo "-- Running clang-tidy on $f"
    clang-tidy -quiet -p=$PWD -header-filter=$dir $f -config="{Checks: '-*,readability-*,-readability-magic-numbers', CheckOptions: [{key: readability-function-size.LineThreshold, value: 200}]}" 2>&1 | \
    awk '!/warnings generated/' | \
    sed -e "s/\(warning:\)/\x1b[33m\1\x1b[0m/g" \
        -e "s/\(error:\)/\x1b[31m\1\x1b[0m/g" \
        -e "s/\(note:\)/\x1b[36m\1\x1b[0m/g" \
        -e "s/\([~^]\)/\x1b[32m\1\x1b[0m/g"
done
