.PHONY: for-nodejs run clean

ARCH := $(shell uname -s)
MAKEFILE_DIR_TMP := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))
MAKEFILE_DIR := $(patsubst %/,%,${MAKEFILE_DIR_TMP})
PROJECT_DIR := $(patsubst %/demo/for-nodejs/,%,${MAKEFILE_DIR_TMP})

SUDOKU_PUZZLE_FILE_PATH := ${PROJECT_DIR}/data/1.sudoku

ifeq (${ARCH}, Darwin)
SUDOKU_LIBRARY_PATH := ${PROJECT_DIR}/buildXcode/sudoku/Debug
endif

ifeq (${ARCH}, Linux)
SUDOKU_LIBRARY_PATH := ${PROJECT_DIR}/build/sudoku
endif

ifeq ($(findstring CYGWIN, ${ARCH}), CYGWIN)
SUDOKU_LIBRARY_PATH := ${PROJECT_DIR}/buildVS/install/bin
SUDOKU_PUZZLE_FILE_PATH := $(subst \,\\,$(shell cygpath -w -a -p ${SUDOKU_PUZZLE_FILE_PATH}))
endif

for-nodejs:
	test -d node_modules || npm install ref ref-array ffi

run:
	LD_LIBRARY_PATH=${SUDOKU_LIBRARY_PATH} node main.js ${SUDOKU_PUZZLE_FILE_PATH}

clean:
	rm -rf ./build/*
