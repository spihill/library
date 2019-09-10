#!/bin/bash

files='files.txt'
touch $files
rm $files
date > $files
python3 listup_source.py3
git add $files
git commit -m "update files.txt" && git push origin master
