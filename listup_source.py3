import glob

file_name = "./files.txt"

try:
	target = open(file_name, 'a')
	files = glob.glob("**/*.cpp", recursive=True)
	for file in files:
		if file.find('verify') != -1 or file.find('test.cpp') != -1 :
			continue;
		target.write(file + '\n')
except Exception as e:
	print(e)
finally:
	target.close()
