CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic

inventory: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o inventory

run: inventory
	./inventory

test: inventory
	./inventory < sample_input.txt > actual_output.txt
	diff -u expected_output.txt actual_output.txt && echo "Project 4 test passed"

clean:
	rm -f inventory actual_output.txt

.PHONY: run test clean
