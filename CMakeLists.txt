cmake_minimum_required(VERSION 3.10)
project(tiny_project)

# Include folder
include_directories(include)

# Common source files
file(GLOB SRC_FILES src/*.cpp)

# Vector Tests
add_executable(TestVector ${SRC_FILES} test/TestVector.cpp)
# Matrix Tests
add_executable(TestMatrix ${SRC_FILES} test/TestMatrix.cpp)
# LinearSystem Tests
add_executable(TestLinearSystem ${SRC_FILES} test/TestLinearSystem.cpp)
# DataParser Tests
add_executable(TestDataParser ${SRC_FILES} test/TestDataParser.cpp)
# Regression Tests
add_executable(TestRegression ${SRC_FILES} test/TestRegression.cpp)
