#!/usr/bin/python3

import glob

file_name = "./files.txt"

ng_words = ['verify/', '.test.cpp','test/','develop/']

try:
	target = open(file_name, 'a')
	files = glob.glob("../../**/*.cpp", recursive=True)
	for file in files:
		ok = 1
		for words in ng_words:
			if file.find(words) != -1:
				ok = 0
		if ok == 1:
			target.write(file[6:] + '\n')
except Exception as e:
	print(e)
finally:
	target.close()
