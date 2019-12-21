cmake_minimum_required(VERSION 3.9) 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
	URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
	SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)
project(viminfo)

hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

#hunter_add_package(Boost COMPONENTS system filesystem)
#find_package(Boost CONFIG REQUIRED system filesystem program_options)

add_library(shell STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/source/shell.cpp
)
add_library(pluginfo STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/source/pluginfo.cpp
)
add_library(webutils STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/source/webutils.cpp
)
target_include_directories(pluginfo
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(shell
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(webutils
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_executable(viminfo source/main.cpp)
target_include_directories(viminfo
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(pluginfo PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(webutils PRIVATE CURL::libcurl)
target_link_libraries(
	viminfo PUBLIC shell pluginfo webutils 
)

