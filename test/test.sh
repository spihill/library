#!/bin/bash
set -e

cd `git rev-parse --show-toplevel`/test

test='.test'
testcase='testcase'

# you can install oj with: $ pip3 install --user -U online-judge-tools=='6.*'
which oj > /dev/null

CXX=${CXX:-g++}
CXXFLAGS="${CXXFLAGS:--std=c++14 -O2 -Wall -g}"
ulimit -s unlimited


list-dependencies() {
	file="$1"
	$CXX $CXXFLAGS -I . -MD -MF /dev/stdout -MM "$file" | sed '1s/[^:].*: // ; s/\\$//' | xargs -n 1
}

list-defined() {
	file="$1"
	$CXX $CXXFLAGS -I . -dM -E "$file"
}

get-url() {
	file="$1"
	list-defined "$file" | grep '^#define PROBLEM ' | sed 's/^#define PROBLEM "\(.*\)"$/\1/'
}

get-last-commit-date() {
    file="$1"
    list-dependencies "$file" | xargs git log -1 --date=iso --pretty=%ad
}

is-verified() {
	file="$1"
	cache=$test/timestamp/$(echo -n "$file" | md5sum | sed 's/ .*//')
	if [[ $MY_GITHUB_ACTION_TEST ]]; then
		timestamp="$(get-last-commit-date "$file")"
		[[ -e $cache ]] && [[ $timestamp = $(cat $cache) ]]
	else
		timestamp="$(list-dependencies "$file" | xargs -I '{}' find "$file" '{}' -printf "%T+\t%p\n" | sort -nr | head -n 1 | cut -f 2)"
		[[ -e $cache ]] && [[ $timestamp -ot $cache ]]
	fi
}

mark-verified() {
	file="$1"
	cache=$test/timestamp/$(echo -n "$file" | md5sum | sed 's/ .*//')
	mkdir -p $test/timestamp
	timestamp="$(get-last-commit-date "$file")"
	echo $timestamp > $cache
}

list-recently-updated() {
	for file in $(find . -name \*.test.cpp) ; do
		list-dependencies "$file" | xargs -n 1 | while read f ; do
			git log -1 --format="%ci	${file}" "$f"
		done | sort -nr | head -n 1
	done | sort -nr | head -n $OJ_TEST_RECENT_FILES_COUNT | cut -f 2
}

run() {
	file="$1"
	url="$(get-url "$file")"
	dir=$test/$(echo -n "$url" | md5sum | sed 's/ .*//')
	mkdir -p ${dir}

	# ignore if IGNORE is defined
	if list-defined "$file" | grep '^#define IGNORE ' > /dev/null ; then
		return
	fi

	if ! is-verified "$file" ; then
		# compile
		$CXX $CXXFLAGS -I . -o ${dir}/a.out "$file"
		if [[ -n ${url} ]] ; then
			# download
			if [[ ! -e ${dir}/$testcase ]] ; then
				sleep 2
				oj download --system "$url" -d ${dir}/$testcase
			fi
			# test
			echo "testing $file"
			oj test -c ${dir}/a.out -d ${dir}/$testcase
		else
		# run
			echo "running $file"
			${dir}/a.out
		fi
		mark-verified "$file"
	fi
}


if [[ $# -eq 0 ]] ; then
	if [[ $MY_GITHUB_ACTION_TEST ]]; then
		echo "run in github action"
		# for f in $(list-recently-updated) ; do
		# 	run $f
		# done
	# else
	fi
	for f in $(find . -name \*.test.cpp) ; do
		run $f
	done
	fi
else
	# specified
	for f in "$@" ; do
		run "$f"
	done
fi
