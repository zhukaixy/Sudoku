cmake_minimum_required(VERSION 3.0)
project(sudokujni
	VERSION 1.0
	# DESCRIPTION "Wrap sudoku dynamic library for java"
	# HOMEPAGE_URL "www.zhyingkun.com"
	LANGUAGES C CXX)

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "CMakeLists.txt for ${PROJECT_NAME}")
message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

if(APPLE)
	set(CMAKE_C_FLAGS         "-std=c11 -Wall -Wextra")
	set(CMAKE_C_FLAGS_DEBUG   "-g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
	include_directories(/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/JavaVM.framework/Headers)
	# /System/Library/Frameworks/JavaVM.framework/Headers
	link_directories(../../../buildXcode/sudoku/Debug)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CMAKE_C_FLAGS         "-std=c11 -Wall -Wextra -Wno-unknown-pragmas")
	set(CMAKE_C_FLAGS_DEBUG   "-g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
	include_directories($ENV{JAVA_HOME}/include)
	include_directories($ENV{JAVA_HOME}/include/linux)
	link_directories(../../../build/sudoku)
elseif(WIN32)
	set(CMAKE_C_FLAGS         "-Wall -DSUDOKU_BUILD_AS_DLL")
	# set(CMAKE_C_FLAGS_DEBUG   "-g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
	include_directories($ENV{JAVA_HOME}/include)
	include_directories($ENV{JAVA_HOME}/include/win32)
	link_directories(../../../buildVS/install/lib)
endif()

include_directories(../../../include)

add_library(${PROJECT_NAME} SHARED SudokuLib.c)

target_link_libraries(${PROJECT_NAME} sudoku)
set_target_properties(${PROJECT_NAME} PROPERTIES
	# FOLDER "sudoku"
	OUTPUT_NAME ${PROJECT_NAME}
	VERSION ${PROJECT_VERSION}
	SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
	POSITION_INDEPENDENT_CODE ON)
