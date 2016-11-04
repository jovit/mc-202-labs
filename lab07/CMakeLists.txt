cmake_minimum_required(VERSION 3.6)
project(lab07)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c")

set(SOURCE_FILES main.c Heap.c Heap.h Utils.c Utils.h Queue.c Queue.h)
add_executable(lab07 ${SOURCE_FILES})