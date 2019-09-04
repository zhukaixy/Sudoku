cmake_minimum_required(VERSION 3.0)
project(Sudoku
	VERSION 1.0
	# DESCRIPTION "Sudoku project" # cmake version >= 3.9
	# HOMEPAGE_URL "www.zhyingkun.com"
	LANGUAGES C CXX)

message(STATUS "CMakeLists.txt for ${PROJECT_NAME}")
message(STATUS "Current OS is ${CMAKE_SYSTEM}")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_SKIP_INSTALL_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FLASE)

add_subdirectory(sudoku)
add_subdirectory(demo)
add_subdirectory(tools)
