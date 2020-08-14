#!/bin/bash
function fuc_arg_arr
{
    local sum=0
    local array
    array=($(echo "$@"))
    for value in ${array[*]}
    do
        sum=$[ $sum + $value ]
    done
    echo $sum
}

array=(1 2 3 4 5)
echo "The original array is: ${array[*]}"
arg1=$(echo ${array[*]})
result=$(fuc_arg_arr $arg1)
echo "The result is $result"

# return arrray

function fuc_arg_arr2
{
    local array
    local newarray
    local elements
    local i
    array=($(echo "$@"))
    newarray=($(echo "$@"))
    elements=$[ $# - 1 ]
    for (( i = 0; i <= $elements; i++ ))
    {
        newarray[$i]=$[ ${array[$i]} * 2 ]
    }
    echo ${newarray[*]}
}
myarray=(1 2 3 4 5)
echo "The original array is ${myarray[*]}"
arg1=$(echo ${myarray[*]})
result=($(fuc_arg_arr2 $arg1))
echo "The new array is ${result[*]}"
