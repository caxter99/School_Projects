cmake_minimum_required(VERSION 3.0)
project(Project3)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES sorting.cpp heapsort.cpp insertsort.cpp mergesort.cpp quicksort.cpp)
add_executable(prj ${SOURCE_FILES})