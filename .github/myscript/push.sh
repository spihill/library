#!/bin/bash

git config --global user.name "spihill"
git config --global user.email "spihill.in@gmail.com"

git checkout -b master
python3 make_cpp_json.py

if [[ $MY_GITHUB_ACTION_TEST ]]; then
	cd ../../../../
	git clone https://spihill:$CPP_JSON_GIST_TOKEN@gist.github.com/spihill/$CPP_JSON_GIST_ID
	cd $CPP_JSON_GIST_ID
	rm ./* -f
	mv ../library/library/.github/myscript/cpp.json .
	git add cpp.json
	stat=`git diff remotes/origin/master | wc -l`
	if [ $stat -eq 0 ]; then
		exit 0
	fi
	git commit -m "update" && git push origin HEAD
fi