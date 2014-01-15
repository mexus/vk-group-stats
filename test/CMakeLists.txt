cmake_minimum_required (VERSION 2.6)
project(VkGroupStat-testing)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set (TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

configure_file (
	"config.cpp.in"
	"${CMAKE_CURRENT_BINARY_DIR}/config.cpp"
)

add_executable(VkGroupStat-testing ${CMAKE_CURRENT_BINARY_DIR}/config.cpp main.cpp csvparsertest.cpp vkdatatest.cpp ../main/helpers/csv_parser.cpp ../main/helpers/csv_filter.cpp ../main/helpers/date_helper.cpp ../main/vk_data.cpp)
