cmake_minimum_required(VERSION 3.21)
project(wg__)

set(CMAKE_CXX_STANDARD 23)
add_executable(wg__ src/main.cpp src/include/assembly-help.h src/include/variables.h src/include/does-it-make-sense.h src/include/generate.h)