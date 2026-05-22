.PHONY: build run clean doxygen docs generate plot report

build:
	mkdir -p bin
	g++ -o bin/main src/main.cpp src/utils.cpp src/sorting.cpp

run: build
	./bin/main

clean:
	rm -rf bin/*
	rm -rf tests/generated/*
	rm -rf tests/results.csv
	rm -rf sorting_performance.png
	rm -rf report.pdf
	rm -rf docs.pdf
	cd doxygen/latex && make clean
	cd ../..

doxygen:
	doxygen Doxyfile

docs: doxygen
	cd doxygen/latex && make
	cd ../..
	cp doxygen/latex/refman.pdf ./docs.pdf

generate:
	tests/generate.py

test:
	tests/test.py

plot:
	tests/plot.py

report: docs.pdf sorting_performance.png
	tests/report.py