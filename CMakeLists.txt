cmake_minimum_required(VERSION 3.21)
project(wgpp)

set(CMAKE_CXX_STANDARD 23)
add_executable(wgpp src/main.cpp src/include/assembly-help.h src/does-it-make-sense.cpp src/include/does-it-make-sense.h src/include/generate.h src/generate.cpp src/lexer.cpp src/include/lexer.h src/template.cpp src/include/template.h src/include/token.h src/include/token-operations.h src/token-operations.cpp src/util.cpp src/include/util.h src/variables.cpp src/include/variables.h src/err-report.cpp)