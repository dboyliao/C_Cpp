#!/bin/sh
name=tom
printName()
{
  echo name is :$name
  name=jim
  echo name is :$name
}
printName;
echo name is :$name
