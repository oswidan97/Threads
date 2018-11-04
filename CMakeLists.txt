cmake_minimum_required(VERSION 3.7)
project(Threads)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c MatrixMultiplication.c MatrixInput.c MatrixMultiplication.h)
add_executable(Threads ${SOURCE_FILES})