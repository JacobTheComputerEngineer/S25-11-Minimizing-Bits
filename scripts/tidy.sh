
#!/bin/sh
# A little bit of a hack, make sure you use the cmake target in the build directory
dir=$PWD
allfiles=`ls $dir/../*.cpp`
for f in $allfiles
do
    clang-tidy -p=$PWD -header-filter=$dir $f -config="{Checks: '-*,readability-*,-readability-magic-numbers', CheckOptions: [{key: readability-function-size.LineThreshold, value: 200}]}"
done
