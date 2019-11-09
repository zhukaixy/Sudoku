cmake_minimum_required(VERSION 3.0)
project(luasudoku
	VERSION 1.0
	# DESCRIPTION "Wrap sudoku dynamic library for lua"
	# HOMEPAGE_URL "www.zhyingkun.com"
	LANGUAGES C CXX
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "CMakeLists.txt for ${PROJECT_NAME}")
message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

if(APPLE)
	set(CMAKE_C_FLAGS         "-std=c11 -Wall -Wextra")
	set(CMAKE_C_FLAGS_DEBUG   "-g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
	link_directories(../../../buildXcode/libsudoku/Debug)
	link_directories(../runtime/macosx)
	set(LIB_OUTPUT_NAME "${PROJECT_NAME}")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CMAKE_C_FLAGS         "-std=c11 -Wall -Wextra -Wno-unknown-pragmas")
	set(CMAKE_C_FLAGS_DEBUG   "-g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
	link_directories(../../../build/libsudoku)
	link_directories(../runtime/linux)
	set(LIB_OUTPUT_NAME "${PROJECT_NAME}")
elseif(WIN32)
	set(CMAKE_C_FLAGS         "-Wall -DSUDOKU_BUILD_AS_DLL -DLUA_BUILD_AS_DLL")
	# set(CMAKE_C_FLAGS_DEBUG   "-g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
	link_directories(../../../buildVS/install/lib)
	link_directories(../runtime/windows)
	set(LIB_OUTPUT_NAME "lib${PROJECT_NAME}")
endif()

include_directories(../../../include)
include_directories(../runtime/include)

aux_source_directory(. LUA_SUDOKU_SRC)

source_group(src FILES ${LUA_SUDOKU_SRC})

add_library(${PROJECT_NAME} SHARED ${LUA_SUDOKU_SRC})

target_link_libraries(${PROJECT_NAME} sudoku lualib)
set_target_properties(${PROJECT_NAME} PROPERTIES
	# FOLDER "sudoku"
	OUTPUT_NAME ${LIB_OUTPUT_NAME}
	VERSION ${PROJECT_VERSION}
	SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
	POSITION_INDEPENDENT_CODE ON
)
