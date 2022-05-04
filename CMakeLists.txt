cmake_minimum_required(VERSION 3.17)
project(PracticePathTracing)

set(CMAKE_CXX_STANDARD 14)

#add_executable(main src/main.cpp)
add_executable(main tests/vec3_test.cpp)
#add_executable(main tests/ray_test.cpp)
#add_executable(main tests/ppm_test.cpp)

target_include_directories(main PRIVATE "include")
#target_compile_features(main PRIVATE cxx_std_17)

