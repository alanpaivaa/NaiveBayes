cmake_minimum_required(VERSION 3.6)
project(untitled)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c csv.h csv.c defines.h util.c util.h extra.h extra.c prediction.h prediction.c)
add_executable(untitled ${SOURCE_FILES})