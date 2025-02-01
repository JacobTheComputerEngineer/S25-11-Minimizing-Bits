
#!/bin/sh
# A little bit of a hack, make sure you use the cmake target in the build directory
for f in $PWD/../*.cpp
do
    # Use clang-tidy with color enabled and filter relevant messages
    clang-tidy -p=$PWD -header-filter=$dir $f -config="{Checks: '-*,readability-*,-readability-magic-numbers', CheckOptions: [{key: readability-function-size.LineThreshold, value: 200}]}" 2>&1 | \
    awk '
        /warning:|error:|note:/ { keep = 3 }  # Start keeping when a warning, error, or note is found
        keep-- >= 0 { print }                 # Print the match and the next 3 lines
    ' | sed -e "s/\(warning:\)/\x1b[33m\1\x1b[0m/g" \
            -e "s/\(error:\)/\x1b[31m\1\x1b[0m/g" \
            -e "s/\(note:\)/\x1b[36m\1\x1b[0m/g" \
            -e "s/\([~^]\)/\x1b[32m\1\x1b[0m/g"
done
