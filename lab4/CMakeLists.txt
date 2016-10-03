cmake_minimum_required(VERSION 3.6)
project(lab04)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
add_executable(lab04 ${SOURCE_FILES})