cmake_minimum_required(VERSION 3.0)
project(tools
	VERSION 1.0.0
	# DESCRIPTION "Tools for sudoku"
	# HOMEPAGE_URL "www.zhyingkun.com"
	LANGUAGES C CXX)

message(STATUS "CMakeLists.txt for ${PROJECT_NAME}")

add_subdirectory(diff-sudoku)
add_subdirectory(format-sudoku)
