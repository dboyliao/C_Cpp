#!/bin/sh
echo please input name:
read name
if test -n $name
then
 echo name is :$name
else
 echo name is null
fi

