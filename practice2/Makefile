.PHONY: build run clean doxygen docs generate plot report

build:
	mkdir -p bin
	g++ -o bin/main src/main.cpp src/utils.cpp src/search.cpp

run: build
	./bin/main

clean:
	rm -rf bin/*
