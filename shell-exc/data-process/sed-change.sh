#!/bin/bash

echo -e "*Replace function: "
# replace
sed '3c\
This is insert line\
And This is also insert line
' ./data-process/test2.txt

echo -e "\n*Mapping function: "
# mapping

sed 'y/123/789/' ./data-process/test2.txt

echo -e "\n*Print function: "
# print

sed -n '/number 1/p' ./data-process/test2.txt

echo -e "\n*Write function: "
# print

sed -n '/number 2/w ./data-process/test-number1.txt' ./data-process/test2.txt