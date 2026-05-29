.PHONY: build run clean doxygen docs generate test plot report

build:
	mkdir -p bin
	g++ -o bin/main src/main.cpp src/aes_prng.cpp src/fib_prng.cpp src/rolling_prng.cpp

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
