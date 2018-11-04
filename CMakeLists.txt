cmake_minimum_required(VERSION 3.7)
project(Threads)

set(CMAKE_C_STANDARD 11)
set(THREADS_PREFER_PTHREAD-FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES main.c MatrixMultiplication.c MatrixInput.c MatrixMultiplication.h)
add_executable(Threads ${SOURCE_FILES})
target_link_libraries(Threads ${CMAKE_THREAD_LIBS_INIT})