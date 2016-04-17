#!/bin/bash 
# -*- coding: utf-8 -*-
count=0
value_array=()

add()
{
    value_array[$count]=$1
    let count++
}

avg()
{
    sum=0
    for val in ${value_array[*]}
    do
        let sum=sum+val
    done
    let avg=sum/count
    echo "Average Value: $avg"
}

max(){
    max_val=${value_array[0]}
    for val in ${value_array[*]}
    do
        if [ $val -gt $max_val ]
        then
            max_val=$val
        fi
    done
    echo "Maximun: $max_val"
}

min(){
    min_val=${value_array[0]}
    for val in ${value_array[*]}
    do
        if [ $val -lt $min_val ]
        then
            min_val=$val
        fi
    done
    echo "Minimum Value: $min_val"
}

show(){
    for val in ${value_array[*]}
    do
        echo "$val"
    done
}

main(){
    echo "Enter a command: "
    read cmd

    if [ $cmd = "exit" ]
    then
        echo "Bye Bye..."
        exit 0
    elif [ $cmd = "add" ]
    then
        echo "Enter a number: "
        read num
        add $num
    elif [ $cmd = "avg" ]
    then
        avg
    elif [ $cmd = "max" ]
    then
        max
    elif [ $cmd = "min" ]
    then
        min
    elif [ $cmd = "show" ]
    then
        show
    fi
    main
}

main
