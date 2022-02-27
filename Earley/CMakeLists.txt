cmake_minimum_required(VERSION 2.8)

########################################
# Project setup
########################################
set(PROJECT_NAME TestSerialization)
project(${PROJECT_NAME})
# After project(..) is called, the following variables are available:
# * PROJECT_SOURCE_DIR - Top level source directory for the project
# * PROJECT_BINARY_DIR - Full path to build directory for project

########################################
# Set up the compiler flags
########################################
set(CMAKE_CXX_STANDARD 11)

########################################
# Define include directories
########################################
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/lib)
include_directories(${COMMON_INCLUDES})

########################################
# Source files
########################################
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/additional.cpp ${PROJECT_SOURCE_DIR}/src/earley.cpp)

########################################
# Compile source files into a library
########################################
add_library(project_lib ${SRC_FILES})

########################################
# Main is separate (e.g. library client)
########################################
add_executable(TestSerialization ${PROJECT_SOURCE_DIR}/src/TestSerialization.cpp)

########################################
# linking Main against the library
########################################
target_link_libraries(TestSerialization project_lib)

########################################
# Testing
########################################
# Options. Turn on with 'cmake -Dmyvarname=ON'.
# option(BUILD_TESTS "Build all tests." ON) # Makes boolean 'test' available.

# google test is a git submodule for the project, and it is also cmake-based
add_subdirectory(./googletest)

enable_testing()
#
# Include the gtest library. gtest_SOURCE_DIR is available due to
# 'project(gtest)' above.
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

########################################
# Standard linking to gtest stuff.
########################################
target_link_libraries(TestSerialization gtest gtest_main)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(TestSerialization "./TestSerialization")
