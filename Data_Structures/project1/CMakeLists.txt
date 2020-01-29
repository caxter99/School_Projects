cmake_minimum_required(VERSION 3.0)
project(Project1)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES components.cpp)
add_executable(prj ${SOURCE_FILES})