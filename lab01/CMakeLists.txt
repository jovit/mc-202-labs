cmake_minimum_required(VERSION 3.6)
project(lab01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c")

set(SOURCE_FILES main.c)
add_executable(lab01 ${SOURCE_FILES})