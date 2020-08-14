#!/bin/bash
# counting files

path=$(echo $PATH | sed 's/:/ /g')
for var in $path; do
    count=0
    if [ -d $var ]; then
        files=$(ls $var)
        IFS_OLD=$IFS
        IFS=$'\t\n'
        for dir in $files; do
            count=$(($count + 1))
        done
        echo "$var - files counts: $count"
        IFS=$IFS
    fi
done
