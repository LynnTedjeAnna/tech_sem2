cmake_minimum_required(VERSION 3.28)
project(sudoku_c C)

set(CMAKE_C_STANDARD 23)
include_directories(include)
include_directories(src)
include_directories(test)

add_executable(sudoku_c main.c
        src/game.c
        src/user_interface.c
        test/test_game.c
        test/test_UI.c
        src/display.c)
