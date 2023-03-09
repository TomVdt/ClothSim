CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++17 -Wall

# CXXFLAGS += -g
CXXFLAGS += -O2
CXXFLAGS += -I src

all:: build test

test: build bin/tests/testVector3d

build/vector3d.o: src/vector3d.cpp src/include/vector3d.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/testVector3d.o: src/test/testVector3d.cpp src/include/vector3d.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/tests/testVector3d: build/testVector3d.o build/vector3d.o
	$(CXX) $(CXXFLAGS) $^ -o $@

build:
	mkdir bin
	mkdir bin
	mkdir bin/app
	mkdir bin/tests

run_tests: test
	for file in bin/tests/*; do ./$$file; done;

clean:
	@echo Removing compiled object files...
	rm -f build/*.o
	@echo Removing executables...
	rm -f bin/app/*
	rm -f bin/tests/*
