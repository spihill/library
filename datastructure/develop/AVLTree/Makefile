all: set.out map.out
set.out: AVLSet.cpp
	g++ -std=c++14 $< -o $@
map.out: AVLMap.cpp
	g++ -std=c++14 $< -o $@
setrun: set.out
	./$<
maprun: map.out
	./$<
