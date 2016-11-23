cmake_minimum_required(VERSION 3.6)
project(lab09)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c")

set(SOURCE_FILES main.c Utils.c Utils.h main.c Heap.c Heap.h)

add_executable(lab09 ${SOURCE_FILES})
