.PHONY: for-cs run clean

ARCH=$(shell uname -s)
MAKEFILE_DIR_TMP=$(dir $(abspath $(lastword ${MAKEFILE_LIST})))
# MAKEFILE_DIR=$(patsubst %/,%,${MAKEFILE_DIR_TMP})
PROJECT_DIR=$(patsubst %/demo/for-cs/,%,${MAKEFILE_DIR_TMP})

ifeq (${ARCH}, Darwin)
SUDOKU_LIBRARY_PATH=${PROJECT_DIR}/buildXcode/sudoku/Debug
endif
ifeq (${ARCH}, Linux)
SUDOKU_LIBRARY_PATH=${PROJECT_DIR}/build/sudoku
endif
ifeq ($(findstring CYGWIN, ${ARCH}), CYGWIN)
SUDOKU_LIBRARY_PATH=${PROJECT_DIR}/buildVS/install/bin
endif

for-cs:
	xbuild for-cs.sln
# msbuild for-cs.sln

run:
	LD_LIBRARY_PATH=${SUDOKU_LIBRARY_PATH} mono ./lib/Debug/for-cs.exe 0<${PROJECT_DIR}/data/1.sudoku

clean:
	rm -rf obj/* lib/*
