#!/bin/bash

git config --global user.name "spihill"
git config --global user.email "spihill.in@gmail.com"
git remote set-url origin https://spihill:${GITHUB_TOKEN}@github.com/spihill/library.git

files='files.txt'
touch $files
rm $files
date > $files
python3 listup_source.py
git add $files
git commit -m "update files.txt" && git push origin master
