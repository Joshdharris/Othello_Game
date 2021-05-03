cmake_minimum_required(VERSION 3.17)
project(Othello_Game C)

set(CMAKE_C_STANDARD 99)

add_executable(Othello_Game Othello.c testCode.c Moves.c Moves.h GlobalValues.h PostWin.c PostWin.h UserInput.c UserInput.h)