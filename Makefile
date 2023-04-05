CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++17 -Wall

# CXXFLAGS += -g
CXXFLAGS += -O2
CXXFLAGS += -I src

all:: build test

test:: build \
	bin/tests/testVector3d \
	bin/tests/testSpring \
	bin/tests/testMasse \
	bin/tests/testIntegrator1 \
	bin/tests/testIntegrator2 \
	bin/tests/testIntegrator3 \
	bin/tests/testIntegrator4

# Compilation modules

build/vector3d.o: src/vector3d.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/constants.o: src/constants.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/masse.o: src/masse.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/spring.o: src/spring.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/integrator.o: src/integrator.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation tests

build/testVector3d.o: src/test/testVector3d.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/testSpring.o: src/test/testSpring.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/testIntegrator1.o: src/test/testIntegrator1.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/testIntegrator2.o: src/test/testIntegrator2.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/testIntegrator3.o: src/test/testIntegrator3.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/testIntegrator4.o: src/test/testIntegrator4.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linking tests

bin/tests/testVector3d: build/testVector3d.o build/vector3d.o build/constants.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests/testSpring: build/testSpring.o build/spring.o build/vector3d.o build/masse.o build/constants.o
	$(CXX) $(CXXFLAGS) $^ -o $@

build/testMasse.o: src/test/testMasse.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/tests/testMasse: build/testMasse.o build/spring.o build/vector3d.o build/masse.o build/constants.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests/testIntegrator1: build/testIntegrator1.o build/integrator.o build/vector3d.o build/masse.o build/spring.o build/constants.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests/testIntegrator2: build/testIntegrator2.o build/integrator.o build/vector3d.o build/masse.o build/spring.o build/constants.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests/testIntegrator3: build/testIntegrator3.o build/integrator.o build/vector3d.o build/masse.o build/spring.o build/constants.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests/testIntegrator4: build/testIntegrator4.o build/integrator.o build/vector3d.o build/masse.o build/spring.o build/constants.o
	$(CXX) $(CXXFLAGS) $^ -o $@

build:
	mkdir bin
	mkdir bin
	mkdir bin/app
	mkdir bin/tests

run_tests: test
	@for file in bin/tests/*; do echo "Running $$file"; ./$$file; done;

clean:
	@echo Removing compiled object files...
	rm -f build/*.o
	@echo Removing executables...
	rm -f bin/app/*
	rm -f bin/tests/*
