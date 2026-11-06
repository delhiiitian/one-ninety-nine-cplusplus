# A Makefile lists targets, what they depend on, and the command to build them.
# Make rebuilds only what changed since last time.
CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic

greeter: main.o greeting.o
	$(CXX) main.o greeting.o -o greeter

main.o: main.cpp greeting.h
	$(CXX) $(CXXFLAGS) -c main.cpp

greeting.o: greeting.cpp greeting.h
	$(CXX) $(CXXFLAGS) -c greeting.cpp

clean:
	rm -f *.o greeter

.PHONY: clean
