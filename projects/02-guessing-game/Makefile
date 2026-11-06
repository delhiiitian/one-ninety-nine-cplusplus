CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic

guessing_game: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o guessing_game

run: guessing_game
	./guessing_game

# Seed 42 always produces the same secret numbers (43, then 18).
test: guessing_game
	./guessing_game 42 < sample_input.txt > actual_output.txt
	diff -u expected_output.txt actual_output.txt && echo "Project 2 test passed"

clean:
	rm -f guessing_game actual_output.txt

.PHONY: run test clean
