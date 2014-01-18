
set (TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

configure_file (
	"config.cpp.in"
	"${CMAKE_CURRENT_BINARY_DIR}/config.cpp"
)

add_executable(VkGroupStat-testing 
        ${CMAKE_CURRENT_BINARY_DIR}/config.cpp
        main.cpp
        csvparsertest.cpp
        vkdatatest.cpp

        ../main/csv/csv_filter.cpp
        ../main/csv/csv_parser.cpp
        ../main/date_helper/date.cpp
        ../main/logging/log.cpp
        ../main/vk/vk_data.cpp

)
