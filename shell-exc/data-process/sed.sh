#!/bin/bash
sed "s/dog/cat/" ./data-process/test.txt
echo 
sed -e "s/brown/green/; s/dog/cat/" ./data-process/test.txt
echo 
sed -e '
s/brown/green/
s/fox/elephant/
s/dog/cat/' ./data-process/test.txt
echo
sed -f ./data-process/sed-test.sed ./data-process/test.txt
echo 
echo "--------------"
sed '2, ${
s/brown/green/
s/fox/elephant/
}' ./data-process/test.txt