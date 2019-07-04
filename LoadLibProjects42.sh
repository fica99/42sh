#!/bin/bash
if [ $# -ne 2 ]; then
	echo "Not a valid number of parameters"
	echo "The first parameter: link to the repository"
	echo "The second parameter: name of hte directory"
	exit
fi
repo=$1
dirname=$2
if [ -d $PWD/$dirname ]; then
	cd $PWD/$dirname && git pull | grep "Already up-to-date";
	if [ $? -eq 1 ]; then
		make -C $PWD
	fi
else
	git clone $repo -b master $libname && make -C $PWD/$dirname
fi
