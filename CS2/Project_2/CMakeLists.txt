
# Requires the `cmake` command to be at least version 2.8.
cmake_minimum_required(VERSION 2.8)


# Declares the project name and its implementation language. "CXX"
# means "C++".
project(towerofhanoi CXX)


# Turn on the generation of test suites. When this command is present
# in the CMakeListst.txt file, it will create a `test` target that
# you can run as:
#
#   make test
#
# from within the build directory.
# enable_testing()


# Update the C++ compiler flags so that we use C++11, not the older
# version of the language, C++03. GCC-4.9, the default compiler in
# our labs works with this setting. So does the default compiler on
# an up-to-date Mac OS X system.
set(CMAKE_CXX_FLAGS -std=c++11)


# Declare that we want to build an executable program named "rc", which
# stands for rational calculator).
add_executable(twhn towerofhanoi.cpp towers.cpp)


# Declare an executable test program and adds it to the test
# suite. This program will be executed when you run
#
#   make test
#
#add_executable(test_rational test_rational.cpp rational.cpp test.cpp)
#add_test(test_rational test_rational)


# DO NOT REMOVE OR MODIFY THIS MACRO.
#
# This creates a new target for the make program. After

# including this, you can write:
#
#     make printout
#
# And the build system will assemble a PDF containing the
# formatted text in the files listed above. The PDF will
# be created in the build directory and is named "printout.pdf".
#
# To use this, add the following to this file:
#
#     add_printout(f1.hpp f1.cpp f2.hpp f2.cpp ...)
#
# Where f1 and f2 are the files that you want to include
# in the printout. Note that header files should always
# precede their source files.
macro(add_printout)
  add_custom_target(printout
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND a2ps -Afill -o- ${ARGN} | ps2pdf - ${CMAKE_BINARY_DIR}/printout.pdf)
endmacro()

# Add files to the output.
add_printout(towerofhanoi.cpp towers.cpp towers.h mystack.h)

