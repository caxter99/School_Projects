cmake_minimum_required(VERSION 3.0)
project(Project2)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Project2.cpp Point.cpp ConvexHull.cpp)
add_executable(prj ${SOURCE_FILES})