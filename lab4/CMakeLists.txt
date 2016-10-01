cmake_minimum_required(VERSION 3.6)
project(lab03)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c MatrioshkaList.c MatrioshkaStack.c Matrioshka.h MallocUtils.c MallocUtils.h)
add_executable(lab03 ${SOURCE_FILES})