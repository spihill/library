#!/bin/bash

s=`git status -s | wc -l`
if [ '0' = $s ]; then
	echo 'This repository is clean.' >&2
	exit 1
fi

files='files.txt'
touch $files
rm $files
date > $files
python3 listup_source.py3
s=`git status -s | wc -l`
if [ '1' = $s ]; then
	git add $files
	git commit -m "update files.txt" && git push origin master
else
	echo 'Please commit except files.txt'
fi