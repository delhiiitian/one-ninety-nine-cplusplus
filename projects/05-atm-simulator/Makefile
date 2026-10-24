CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic

atm: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o atm

run: atm
	./atm

test: atm
	./atm < sample_input.txt > actual_output.txt
	diff -u expected_output.txt actual_output.txt && echo "Project 5 test passed"

clean:
	rm -f atm actual_output.txt

.PHONY: run test clean
