#!/usr/bin/python3

import glob
import json
import codecs

def file_list():
	ng_words = ['verify/', '.test.cpp','test/','develop/']
	result = []
	files = glob.glob("../../**/*.cpp", recursive=True)
	for file in files:
		ok = 1
		for words in ng_words:
			if file.find(words) != -1:
				ok = 0
		if ok == 1:
			result.append(file)
	return result

def prefix_name(s):
	start = s.rfind('/') + 1
	end = s.rfind('.')
	return s[start:end]

def source_load(name):
	try:
		src = codecs.open(name, 'r', 'utf-8')
		return src
	except Exception as e:
		print(e)
		src.close()
		exit(1)

def make_cpp_json(target):
	sources = file_list()
	result = {}
	for source_name in sources:
		src = source_load(source_name)
		src_dict = {}
		prefix = prefix_name(source_name)
		src_dict['prefix'] = prefix
		body = []
		for line in src:
			if line[-1] == '\n':
				body.append(line[:-1])
			else:
				body.append(line)
		src_dict['body'] = body
		result[prefix] = src_dict
		src.close()
	json.dump(result, target, indent='\t')


if __name__ == '__main__':
	target_name = "cpp.json"
	try:
		target = codecs.open(target_name, 'w', 'utf-8')
		make_cpp_json(target)
	except Exception as e:
		print(e)
		exit(1)
	finally:
		target.close()
	