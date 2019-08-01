cmake_minimum_required(VERSION 3.13)
project(8_puzzle)

set(CMAKE_CXX_STANDARD 14)

add_executable(8_puzzle main.cpp PuzzleBoard.cpp PuzzleBoard.h)