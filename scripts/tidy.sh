#!/bin/sh
# assumes root is defined as CMAKE_SOURCE_DIR
for f in ${ROOT}/*.cpp
do
    echo "-- Running clang-tidy on $f"
    clang-tidy -quiet -p=$PWD -header-filter=$dir $f -config="{Checks: '-*,readability-*,-readability-magic-numbers', CheckOptions: [{key: readability-function-size.LineThreshold, value: 200}]}"
done
