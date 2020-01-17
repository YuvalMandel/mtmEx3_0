cmake_minimum_required(VERSION 3.15)
project(mtmEx3_0)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")



add_executable(mtmEx3_0
        #Time.cpp
        MtmParkingLot.cpp
        ParkingLotPrinter.cpp
        ParkingLot.cpp
        ParkingSpot.cpp

)
