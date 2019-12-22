cmake_minimum_required(VERSION 3.9) 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
	URL "https://github.com/cpp-pm/hunter/archive/v0.23.240.tar.gz"
	SHA1 "ca19f3769e6c80cfdd19d8b12ba5102c27b074e0"
)

#HunterGate(
#	URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
#    SHA1 "9a3594a61227967fb92159339ba326701b287b19"	
#)
project(viminfo)

hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS system filesystem program_options)
find_package(Boost CONFIG REQUIRED system filesystem program_options)

add_executable(
		${PROJECT_NAME}
		${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/source/shell.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/source/singleton.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/source/plugin.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/source/webutils.cpp
)
target_include_directories(
		${PROJECT_NAME}
		PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/tools/boost-process/include
)
target_link_libraries(
		${PROJECT_NAME}
		Boost::filesystem
		Boost::system
		CURL::libcurl
		nlohmann_json::nlohmann_json
)
