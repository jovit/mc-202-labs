cmake_minimum_required(VERSION 3.6)
project(lab10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c")

set(SOURCE_FILES main.c HashTable.c HashTable.h Utils.c Utils.h)

add_executable(lab10 ${SOURCE_FILES})
