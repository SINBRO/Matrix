cmake_minimum_required(VERSION 3.13)
project(Matrix)

set(CMAKE_CXX_STANDARD 14)

add_executable(matrix main.cpp Matrix.h Matrix.cpp)