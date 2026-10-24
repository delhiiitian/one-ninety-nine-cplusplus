# Works without CMake. With CMake: cmake -S . -B build && cmake --build build && ctest --test-dir build
CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -Iinclude
LIB_OBJS = build/point.o build/shapes.o build/units.o

all: build/plot_calculator build/geometry_tests

build/%.o: src/%.cpp include/geometry/*.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/libgeometry.a: $(LIB_OBJS)
	ar rcs $@ $(LIB_OBJS)

build/plot_calculator: apps/plot_calculator.cpp build/libgeometry.a
	$(CXX) $(CXXFLAGS) $< -Lbuild -lgeometry -o $@

build/geometry_tests: tests/test_geometry.cpp tests/test_framework.h build/libgeometry.a
	$(CXX) $(CXXFLAGS) $< -Lbuild -lgeometry -o $@

run: build/plot_calculator
	./build/plot_calculator < sample_input.txt

test: all
	./build/geometry_tests
	./build/plot_calculator < sample_input.txt > build/actual_output.txt
	diff -u expected_output.txt build/actual_output.txt && echo "Project 7 test passed"

clean:
	rm -rf build

.PHONY: all run test clean
