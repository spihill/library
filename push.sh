#!/bin/bash
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
