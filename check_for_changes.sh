#!/bin/sh
p=$(pwd)
for dir in $( ls -1 ); do echo "$dir>>>>>>>>>>>>>>>"; cd $dir; git status; echo "-------------------------------$?-------------------"; cd $p; done
