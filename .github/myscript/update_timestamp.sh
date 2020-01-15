#!/bin/bash

git config --global user.name "spihill"
git config --global user.email "spihill.in@gmail.com"

if [[ $MY_GITHUB_ACTION_TEST ]]; then
	cd ../../test/mytest/.test/timestamp
	git add .
	git commit -m "update" && git push origin HEAD || echo "NOT changed"
fi