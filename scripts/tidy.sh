#!/bin/sh
# A little bit of a hack but it works, make sure to use the cmake target from the build directory
for f in $PWD/../*.cpp
do
    echo "-- Running clang-tidy on $f"
    clang-tidy -quiet -p=$PWD -header-filter=$dir $f -config="{Checks: '-*,readability-*,-readability-magic-numbers', CheckOptions: [{key: readability-function-size.LineThreshold, value: 200}]}"
done
