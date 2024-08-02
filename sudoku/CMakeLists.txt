cmake_minimum_required(VERSION 3.28)
project(sudoku C)

set(CMAKE_C_STANDARD 23)
include_directories(src, include)
add_executable(sudoku src/main.c
        include/board.h
        src/board.c)
