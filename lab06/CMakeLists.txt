cmake_minimum_required(VERSION 3.6)
project(lab06)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c")

set(SOURCE_FILES main.c Utils.c TreeAVL.c TreeAVL.h SplayTree.c SplayTree.h Queue.c Queue.h Ingredient.h Ingredient.c)
add_executable(lab06 ${SOURCE_FILES})