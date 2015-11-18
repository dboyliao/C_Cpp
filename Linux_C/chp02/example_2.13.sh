#!/bin/sh
type="";
echo input your type:
read type
until [ $type = "quit" ]
do 
  echo "your input is :"$type
  echo input your type:
  read type
done
