cmake_minimum_required(VERSION 3.0)
project(sudoku
	VERSION 1.0
	# DESCRIPTION "Sudoku dynamic library"
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
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CMAKE_C_FLAGS         "-std=c11 -Wall -Wextra")
	set(CMAKE_C_FLAGS_DEBUG   "-g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
elseif(WIN32)
	set(CMAKE_C_FLAGS         "-std=c11 -Wall -DSUDOKU_BUILD_AS_DLL")
	set(CMAKE_C_FLAGS_DEBUG   "-g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
endif()

include_directories(../include)
include_directories(./src)

aux_source_directory(./src SUDOKU_SRC)
file(GLOB SUDOKU_HEADERS "../include/*.h")
file(GLOB SUDOKU_PRIVATE_HEADERS "./include/*.h")

source_group(src FILES ${SUDOKU_SRC})
source_group(include FILES ${SUDOKU_HEADERS})
source_group(private FILES ${SUDOKU_PRIVATE_HEADERS})

add_library(${PROJECT_NAME} SHARED 
	${SUDOKU_SRC}
	${SUDOKU_HEADERS}
	${SUDOKU_PRIVATE_HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER "sudoku"
	OUTPUT_NAME ${PROJECT_NAME}
	VERSION ${PROJECT_VERSION}
	SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
	POSITION_INDEPENDENT_CODE ON)

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
install(FILES ${SUDOKU_HEADERS} DESTINATION include)

add_subdirectory(test)
