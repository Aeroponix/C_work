#!/bin/bash
make clean
make

./a.out main_input.txt > output.txt

if diff main_input.txt output.txt > /dev/null ; then
	echo Success
else
	echo Fail
fi
