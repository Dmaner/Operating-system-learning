#!/bin/bash
echo "Test Line 2" | sed 'i\Test Line 1'

# insert before index 3
sed '3i\
This is insert line\
And This is also insert line
' ./data-process/test2.txt

# append after index 3
echo -e "\n**************"
sed '3a\
This is append line' ./data-process/test2.txt