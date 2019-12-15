cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
	URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
	SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)
project(viminfo)

add_executable(viminfo source/main.cpp)
add_library(tools STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/source/tools.cpp
)
add_library(crawler STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/source/crawler.cpp
)
target_include_directories(viminfo
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(crawler
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(tools
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(viminfo tools crawler)

