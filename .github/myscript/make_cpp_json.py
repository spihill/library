#!/usr/bin/python3

import glob
import json
import codecs

def file_list(not_need):
	ng_words = ['verify/', '.test.cpp','test/','develop/']
	not_need_words = ['for_include']
	result = []
	files = glob.glob("../../**/*.cpp", recursive=True)
	for file in files:
		ok = 1
		for words in ng_words:
			if file.find(words) != -1:
				ok = 0
		if ok == 1:
			result.append(file)
		ok = 1
		for words in not_need_words:
			if file.find(words) != -1:
				ok = 0
		if ok == 0:
			not_need.append(file)
	return result

def prefix_name(s):
	start = s.rfind('/') + 1
	end = s.rfind('.')
	return s[start:end]

def prefix_name_include(s):
	start = max(s.rfind('/'), s.find('"')) + 1
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

def make_dict_dfs(prefix, depends, bodies, positions, indents, result):
	if prefix in result:
		return
	result[prefix] = {}
	result[prefix]['prefix'] = prefix
	result[prefix]['body'] = []
	prefixies = []
	for dep in depends[prefix]:
		make_dict_dfs(dep, depends, bodies, positions, indents, result)
		prefixies.append(dep)
	pidx = 0
	for idx, line in enumerate(bodies[prefix]):
		if positions[prefix][pidx] == idx:
			for line_2 in result[prefixies[pidx]]['body']:
				result[prefix]['body'].append(indents[prefix][pidx] + line_2)
			pidx += 1
		else:
			result[prefix]['body'].append(line)

def make_cpp_json(target):
	not_need = []
	sources = file_list(not_need)
	depends = {}
	positions = {}
	indents = {}
	bodies = {}
	result = {}
	prefixies = []
	for source_name in sources:
		src = source_load(source_name)
		src_dict = {}
		prefix = prefix_name(source_name)
		prefixies.append(prefix)
		bodies[prefix] = []
		depends[prefix] = []
		positions[prefix] = []
		indents[prefix] = []
		for idx, line in enumerate(src):
			if '#include' in line and '"' in line:
				depends[prefix].append(prefix_name_include(line))
				positions[prefix].append(idx)
				indents[prefix].append(line[0:line.find('#')])
				bodies[prefix].append('')
			elif line[-1] == '\n':
				bodies[prefix].append(line[:-1])
			else:
				bodies[prefix].append(line)
		positions[prefix].append(1000000000)
		src.close()
	result = {}
	for pref in prefixies:
		make_dict_dfs(pref, depends, bodies, positions, indents, result)
	for nn in not_need:
		result.pop(prefix_name(nn))
	json.dump(result, target, indent='\t')
	print('Made ' + str(len(result)) + ' snipetts')
	count = 1
	for pref in result:
		print(' ' + str(count) + '. ' + pref)
		count += 1


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
	