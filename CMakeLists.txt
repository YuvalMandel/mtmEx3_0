cmake_minimum_required(VERSION 3.15)
project(mtmEx3_0)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(mtmEx3_0
        main2.cpp
        UniqueArray.h
        UniqueArrayImp.h)
