cmake_minimum_required (VERSION 2.6)
project(VkGroupStat)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror -Wall -Wextra")

add_subdirectory(main)
add_subdirectory(test)

