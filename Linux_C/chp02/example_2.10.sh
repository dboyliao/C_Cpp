#!/bin/sh
echo please input your name:
read name
case $name in
tom)
  echo your name is tom
;;
jim)
  echo your name is jim
  ;;
*)
  echo "sorry we don't konw your name"
  ;;
esac
