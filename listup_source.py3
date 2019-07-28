import glob

file_name = "./files.txt"

try:
	target = open(file_name, 'a')
	files = glob.glob("*/*/*.cpp")
	for file in files:
		target.write(file + '\n')
	files = glob.glob("*/*.cpp")
	for file in files:
		target.write(file + '\n')
except Exception as e:
	print(e)
finally:
	target.close()
