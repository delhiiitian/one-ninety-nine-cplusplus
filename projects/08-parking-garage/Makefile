CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic
SOURCES = src/main.cpp src/garage.cpp src/vehicle.cpp
HEADERS = src/garage.h src/vehicle.h src/money.h

parking_garage: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o parking_garage

run: parking_garage
	./parking_garage

test: parking_garage
	./parking_garage < sample_input.txt > actual_output.txt
	diff -u expected_output.txt actual_output.txt && echo "Project 8 test passed"

clean:
	rm -f parking_garage actual_output.txt

.PHONY: run test clean
