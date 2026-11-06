CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic

report: main.cpp libstats.a
	$(CXX) $(CXXFLAGS) main.cpp -L. -lstats -o report

# A static library is an archive (.a) of compiled object files.
libstats.a: stats/stats.cpp stats/stats.h
	$(CXX) $(CXXFLAGS) -c stats/stats.cpp -o stats.o
	ar rcs libstats.a stats.o

clean:
	rm -f *.o *.a report

.PHONY: clean
