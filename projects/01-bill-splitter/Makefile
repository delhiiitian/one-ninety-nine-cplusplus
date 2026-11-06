CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic

bill_splitter: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o bill_splitter

run: bill_splitter
	./bill_splitter

test: bill_splitter
	./bill_splitter < sample_input.txt > actual_output.txt
	diff -u expected_output.txt actual_output.txt && echo "Project 1 test passed"

clean:
	rm -f bill_splitter actual_output.txt

.PHONY: run test clean
