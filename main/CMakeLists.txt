cmake_minimum_required (VERSION 2.6)
project(VkGroupStat)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(VkGroupStat main.cpp helpers/csv_parser.cpp helpers/csv_filter.cpp helpers/date_helper.cpp helpers/log_helper.cpp vk_data.cpp)

