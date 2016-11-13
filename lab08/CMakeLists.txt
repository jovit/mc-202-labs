cmake_minimum_required(VERSION 3.6)
project(lab08)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c")

set(SOURCE_FILES main.c Utils.c Utils.h TreeAVL.c TreeAVL.h HashTable.c HashTable.h)
add_executable(lab08 ${SOURCE_FILES})
