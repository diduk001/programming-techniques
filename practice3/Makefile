.PHONY: build run clean doxygen docs generate test time plot report

build:
	mkdir -p bin
	g++ -o bin/main src/main.cpp src/aes_prng.cpp src/fib_prng.cpp src/rolling_prng.cpp src/statistc_tests.cpp src/prng_tests.cpp src/utils.cpp

run: build
	mkdir -p tests/results
	./bin/main

time: build
	mkdir -p tests/results
	./bin/main tests/results/results.csv

plot: time
	python3 tests/plot.py

report:
	python3 tests/report.py

clean:
	rm -rf bin/*
	rm -rf tests/results
	cd doxygen/latex && make clean
	cd ../..

doxygen:
	doxygen Doxyfile

docs: doxygen
	cd doxygen/latex && make
	cd ../..
	cp doxygen/latex/refman.pdf ./docs.pdf
