cmake_minimum_required(VERSION 3.16)
project(GeometryLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. The library: reusable code, no main().
add_library(geometry STATIC src/point.cpp src/shapes.cpp src/units.cpp)
target_include_directories(geometry PUBLIC include)
target_compile_options(geometry PRIVATE -Wall -Wextra -pedantic)

# 2. An application that uses the library.
add_executable(plot_calculator apps/plot_calculator.cpp)
target_link_libraries(plot_calculator PRIVATE geometry)

# 3. Unit tests, run with: ctest --test-dir build
enable_testing()
add_executable(geometry_tests tests/test_geometry.cpp)
target_link_libraries(geometry_tests PRIVATE geometry)
add_test(NAME geometry_tests COMMAND geometry_tests)
