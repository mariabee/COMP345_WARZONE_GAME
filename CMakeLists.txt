cmake_minimum_required(VERSION 3.15)
project(COMP345_WARZONE_GAME)

set(CMAKE_CXX_STANDARD 14)

include_directories("Part 1")
include_directories("Part 2")
include_directories("Part 3")
include_directories("Part 5")

add_executable(COMP345_WARZONE_GAME
        "Part 1/Map.cpp"
        "Part 1/Map.h"
        "Part 1/MapDriver.cpp"
        )
     

