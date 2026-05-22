.PHONY: build run clean doxygen docs generate test plot report

build:
	mkdir -p bin
	g++ -o bin/main src/main.cpp src/utils.cpp src/search.cpp

run: build
	./bin/main

clean:
	rm -rf tests/generated/*
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
	tests/generate.py

test: build generate
	python3 tests/test.py

plot:
	python3 tests/plot.py

report:
	python3 tests/report.py
