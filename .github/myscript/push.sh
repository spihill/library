#!/bin/bash

git config --global user.name "spihill"
git config --global user.email "spihill.in@gmail.com"
if [[ $MY_GITHUB_ACTION_TEST ]]; then
	git remote set-url origin https://spihill:${GITHUB_TOKEN}@github.com/spihill/library.git
else
	git remote set-url origin git@github.com:spihill/library.git
fi

git checkout -b update-files
git pull
git merge master
git push origin HEAD

files='files.txt'
touch $files
rm $files
date > $files
python3 listup_source.py
git add $files
git commit -m "update files.txt" && git push origin HEAD
