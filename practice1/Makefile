.PHONY: build run clean doxygen docs generate

build:
	mkdir -p bin
	g++ -o bin/main src/main.cpp src/utils.cpp src/sorting.cpp

run: build
	./bin/main

clean:
	rm -rf bin/*
	cd doxygen/latex && make clean
	cd ../..

doxygen:
	doxygen Doxyfile

docs: doxygen
	cd doxygen/latex && make
	cd ../..
	cp doxygen/latex/refman.pdf ./docs.pdf

generate:
	tests/main.py
