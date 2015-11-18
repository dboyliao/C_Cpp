#!/bin/sh
count=0
valueset=()

add()
{
  valueset[$count]=$1
  let count++
}
list()
{
 for temp in ${valueset[*]}
 do
   echo $temp
 done
}
max()
{
 maxvalue=0
 for temp in ${valueset[*]}
 do
  if [ $maxvalue -lt $temp ]; then
     maxvalue=$temp
  fi
 done
 echo "max value is :"$maxvalue
}
min()
{
 minvalue=${valueset[0]}
 for temp in ${valueset[*]}
 do
  if [ $temp -lt $minvalue ]; then
     minvalue=$temp
  fi  
 done 
 echo "min value is :"$minvalue
}
avg()
{
 avgvalue=0
 for temp in ${valueset[*]}
 do
     let avgvalue=temp+avgvalue
 done
  let avg=avgvalue/count
 echo "avg value is :"$avg

}
main()
{
  echo please input cmd:
  read key value
  if [ $key = "add" ];  then
    add $value
  elif [ $key = "avg" ];  then
    avg
  elif [ $key = "max" ];  then
    max
  elif [ $key = "list" ]; then
    list
  elif [ $key = "min" ]; then
    min
  elif [ $key = "quit" ]; then
    return
 fi
 main
}
main
