.PHONY: build run clean doxygen latex

build:
	g++ -o bin/main src/main.cpp

run: build
	./bin/main

clean:
	rm -rf bin/*
	cd doxygen/latex && make clean
	cd ../..

doxygen:
	doxygen Doxyfile

latex: doxygen
	cd doxygen/latex && make
	cd ../..
	cp doxygen/latex/refman.pdf ./docs.pdf
