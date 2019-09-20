.PHONY: for-lua run clean

ARCH=$(shell uname -s)
MAKEFILE_DIR_TMP=$(dir $(abspath $(lastword ${MAKEFILE_LIST})))
MAKEFILE_DIR=$(patsubst %/,%,${MAKEFILE_DIR_TMP})
PROJECT_DIR=$(patsubst %/demo/for-lua/,%,${MAKEFILE_DIR_TMP})

SUDOKU_INCLUDE_PATH=${PROJECT_DIR}/include
LUA_INCLUDE_PATH=${MAKEFILE_DIR}/runtime/include

ifeq (${ARCH}, Darwin)
SUDOKU_LIBRARY_PATH=${PROJECT_DIR}/buildXcode/sudoku/Debug
SUDOKU_LIBRARY_NAME=lualib.5.3

LUA_RUNTIME_PATH=${MAKEFILE_DIR}/runtime/macosx
LUA_SUDOKU_LIB_NAME=build/libluasudoku.so
LUA_SEARCH_CPATH=${MAKEFILE_DIR}/build/?.so

COMPILE_FLAG=-bundle

LUA_EXE=${LUA_RUNTIME_PATH}/lua
endif

ifeq (${ARCH}, Linux)
SUDOKU_LIBRARY_PATH=${PROJECT_DIR}/build/sudoku
SUDOKU_LIBRARY_NAME=lualib

LUA_RUNTIME_PATH=${MAKEFILE_DIR}/runtime/linux
LUA_SUDOKU_LIB_NAME=build/libluasudoku.so
LUA_SEARCH_CPATH=${MAKEFILE_DIR}/build/?.so

COMPILE_FLAG=-shared -std=c11

LUA_EXE=${LUA_RUNTIME_PATH}/lua
endif

ifeq ($(findstring CYGWIN, ${ARCH}), CYGWIN)
SUDOKU_LIBRARY_PATH=${PROJECT_DIR}/buildVS/install/bin
SUDOKU_LIBRARY_NAME=lualib

LUA_RUNTIME_PATH=${MAKEFILE_DIR}/runtime/windows
LUA_SUDOKU_LIB_NAME=build/libluasudoku.dll
LUA_SEARCH_CPATH=${MAKEFILE_DIR}/build/?.dll

COMPILE_FLAG=-shared

LUA_EXE=${LUA_RUNTIME_PATH}/lua.exe
endif

for-lua:
	gcc -I${SUDOKU_INCLUDE_PATH} -I${LUA_INCLUDE_PATH}  -L${SUDOKU_LIBRARY_PATH}  -L${LUA_RUNTIME_PATH} -o ${LUA_SUDOKU_LIB_NAME} -fPIC ${COMPILE_FLAG} cmod/luasudoku.c -l${SUDOKU_LIBRARY_NAME} -lsudoku

run:
	LD_LIBRARY_PATH=${SUDOKU_LIBRARY_PATH}:${LUA_RUNTIME_PATH} LUA_CPATH=${LUA_SEARCH_CPATH} ${LUA_EXE} ./main.lua nice 0<${PROJECT_DIR}/data/1.sudoku

clean:
	rm -rf ./build/*
