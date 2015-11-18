#!/bin/sh
name=(tom jim jane test)
name[0]=myself
echo ${name[@]}
unset name[0]
echo ${name[@]}
unset name[@]
echo ${name[*]}
name[0]=myself
name[1]=tom
echo ${name[@]}
