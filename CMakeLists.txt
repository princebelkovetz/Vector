cmake_minimum_required(VERSION 3.21.1)
project(vector)

set(CMAKE_CXX_STANDARD 20)

find_package(Catch2)

add_executable(vector test/test.cpp src/vector.cpp src/vector.cpp src/vector.h test/test.cpp)
target_link_libraries(vector PRIVATE Catch2::Catch2WithMain)