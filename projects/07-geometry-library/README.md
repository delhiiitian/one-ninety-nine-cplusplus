# Project 7: Geometry Library with Tests

A small, reusable C++ library for measuring shapes (points, circles,
rectangles, triangles and any polygon), packaged the way professional
libraries are: public headers in `include/`, implementation in `src/`, an
application in `apps/`, and unit tests in `tests/`. It builds with CMake or
with plain Make.

The demo app, `plot_calculator`, measures a land plot from its corner
coordinates: area in square metres, square feet and guntha, boundary length,
fencing cost, and the smallest rectangle it fits in.

It uses Chapter 7 ideas: headers and sources, `#pragma once`, namespaces, a
static library, Make and CMake, warnings, and unit tests.

## Layout

```
include/geometry/   point.h  shapes.h  units.h     public headers (the library's "menu")
src/                point.cpp shapes.cpp units.cpp  implementation, compiled into libgeometry.a
apps/               plot_calculator.cpp             a program that uses the library
tests/              test_framework.h test_geometry.cpp  25 unit checks
CMakeLists.txt      library + app + tests (ctest)
Makefile            the same build without CMake
```

## Build and test

```sh
make test                  # builds into build/, runs the unit tests and the app test

# or with CMake
cmake -S . -B build
cmake --build build
ctest --test-dir build
./build/plot_calculator < sample_input.txt
```

## Ideas to extend

- Add `Ellipse` with `area` and an approximate `perimeter`.
- Add `bool contains(const Polygon&, const Point&)` using the ray-casting rule.
