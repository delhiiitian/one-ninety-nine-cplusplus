# CMake describes the project once and generates build files for any platform
# (Makefiles, Ninja, Visual Studio, Xcode).
cmake_minimum_required(VERSION 3.16)
project(Greeter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(greeter main.cpp greeting.cpp)
target_compile_options(greeter PRIVATE -Wall -Wextra -pedantic)
