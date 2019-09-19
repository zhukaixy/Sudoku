.PHONY: for-cs run clean

ARCH=$(shell uname -s)
MAKEFILE_DIR=$(dir $(abspath $(lastword ${MAKEFILE_LIST})))
PROJECT_DIR=$(patsubst %/demo/for-cs/,%,${MAKEFILE_DIR})

ifeq (${ARCH}, Darwin)
MAKE_LIBRARY_PATH=${PROJECT_DIR}/buildXcode/sudoku/Debug
endif
ifeq (${ARCH}, Linux)
MAKE_LIBRARY_PATH=${PROJECT_DIR}/build/sudoku
endif
ifeq ($(findstring CYGWIN, ${ARCH}), CYGWIN)
MAKE_LIBRARY_PATH=${PROJECT_DIR}/buildVS/install/bin
endif

for-cs:
	xbuild for-cs.sln
# msbuild for-cs.sln

run:
	LD_LIBRARY_PATH=${MAKE_LIBRARY_PATH} mono ./lib/Debug/for-cs.exe 0<${PROJECT_DIR}/data/1.sudoku

clean:
	rm -rf obj/* lib/*
