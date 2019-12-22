cmake_minimum_required(VERSION 3.9) 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
	URL "https://github.com/cpp-pm/hunter/archive/v0.23.240.tar.gz"
	SHA1 "ca19f3769e6c80cfdd19d8b12ba5102c27b074e0"
)
project(viminfo)

hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS system filesystem program_options)
find_package(Boost CONFIG REQUIRED system filesystem program_options)

#hunter_add_package(BoostProcces)
#find_package(BoostProcces CONFIG REQUIRED)

add_library(shell STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/source/shell.cpp
)
add_library(plugin STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/source/plugin.cpp
)
add_library(webutils STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/source/webutils.cpp
)
add_library(vimconfig STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/source/singleton.cpp
)
target_include_directories(plugin
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(shell
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(webutils
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(vimconfig
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_executable(
		viminfo source/main.cpp
)
target_include_directories(viminfo
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(vimconfig PUBLIC
	Boost::filesystem Boost::system)
target_link_libraries(
		plugin PUBLIC nlohmann_json::nlohmann_json
)
target_link_libraries(
		webutils PRIVATE CURL::libcurl
)

target_link_libraries(
	viminfo PUBLIC shell vimconfig plugin webutils
)

