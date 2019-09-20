#!/bin/bash

git config --global user.name "spihill"
git config --global user.email "spihill.in@gmail.com"
if [[ $MY_GITHUB_ACTION_TEST ]]; then
	pwd
	ls
	cd ../../../../
	ls
	git clone https://spihill:$CPP_JSON_GIST_TOKEN@gist.github.com/spihill/$CPP_JSON_GIST_ID
	ls
fi

# git checkout -b update-files
# git branch --set-upstream-to=origin/update-files update-files
# git pull
# git merge origin/master

files='files.txt'
rm -f $files
date > $files
python3 listup_source.py
git add $files
git commit -m "update files.txt" && git push origin HEAD
