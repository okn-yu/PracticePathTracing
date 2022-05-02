cmake_minimum_required(VERSION 3.17)
project(PathTracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(PathTracer main.cpp vec3.h)
#add_executable(PathTracer test/vec3_test.cpp vec3.h)