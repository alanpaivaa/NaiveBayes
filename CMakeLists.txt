cmake_minimum_required(VERSION 3.6)
project(untitled)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES prediction/main.c prediction/csv.h prediction/csv.c prediction/defines.h prediction/util.c prediction/util.h prediction/extra.h prediction/extra.c prediction/prediction.h prediction/prediction.c)
add_executable(untitled ${SOURCE_FILES})