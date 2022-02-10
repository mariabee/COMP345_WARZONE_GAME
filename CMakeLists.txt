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
        "Part 2/Player.cpp"
        "Part 2/Player.h"
        "Part 2/PlayerDriver.cpp"
        "Part 3/Orders.cpp"
        "Part 3/Orders.h"
        "Part 3/OrdersDriver.cpp"
        "Part 5/GameEngine.cpp"
        "Part 5/GameEngine.h"
        "Part 5/GameEngineDriver.cpp"
        "Part 3/OrdersDriver.cpp" 
     

