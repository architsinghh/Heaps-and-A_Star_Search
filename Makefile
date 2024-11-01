compiler = g++
flags = -g -Wall -std=c++11
compile = $(compiler) $(flags)

doublet: doublet.cpp MinHeap.h
	$(compile) $< -o $@

.PHONY: clean
clean:
	rm -rf *.o doublet
