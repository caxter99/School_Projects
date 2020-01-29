cmake_minimum_required(VERSION 3.0)
project(Project2)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES empmaps.cpp Employee.cpp empdriver.cpp)
add_executable(prj ${SOURCE_FILES})