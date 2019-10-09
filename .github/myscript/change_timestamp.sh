#!/bin/bash

git config --global user.name "spihill"
git config --global user.email "spihill.in@gmail.com"

if [[ $MY_GITHUB_ACTION_TEST ]]; then
	cd ../../test/.test
	ls
	rm -rf ./timestamp
	git clone https://spihill:$CPP_JSON_GIST_TOKEN@gist.github.com/spihill/$TIMESTAMP_GIST_ID
	mv $TIMESTAMP_GIST_ID timestamp
	ls
fi