CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++17 -Wall

# CXXFLAGS += -g
CXXFLAGS += -O2

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

CXXFLAGS += -I $(SRC_DIR)

all:: test

test: testVector3d

vector3d.o: src/vector3d.cpp src/include/vector3d.h
	$(CXX) $(CXXFLAGS) -c $< -o $(BUILD_DIR)/$@

testVector3d.o: src/test/testVector3d.cpp src/include/vector3d.h
	$(CXX) $(CXXFLAGS) -c $< -o $(BUILD_DIR)/$@

testVector3d: testVector3d.o vector3d.o
	$(CXX) $(CXXFLAGS) $(addprefix $(BUILD_DIR)/, $^) -o $(BIN_DIR)/tests/$@

clean:
	@echo Removing compiled object files...
	rm -f $(BUILD_DIR)/*.o;
