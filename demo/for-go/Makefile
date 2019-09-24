.PHONY: for-go run clean

ARCH := $(shell uname -s)
MAKEFILE_DIR_TMP := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))
# MAKEFILE_DIR := $(patsubst %/,%,${MAKEFILE_DIR_TMP})
PROJECT_DIR := $(patsubst %/demo/for-go/,%,${MAKEFILE_DIR_TMP})

SUDOKU_INCLUDE_PATH := ${PROJECT_DIR}/include

ifeq (${ARCH}, Darwin)
SUDOKU_LIBRARY_PATH := ${PROJECT_DIR}/buildXcode/sudoku/Debug
endif
ifeq (${ARCH}, Linux)
SUDOKU_LIBRARY_PATH := ${PROJECT_DIR}/build/sudoku
endif
# Current Do Not Support Windows+Cygwin
# ifeq ($(findstring CYGWIN, ${ARCH}), CYGWIN)
# SUDOKU_LIBRARY_PATH := ${PROJECT_DIR}/buildVS/install/bin
# endif

for-go:
	CGO_CFLAGS=-I${SUDOKU_INCLUDE_PATH} CGO_LDFLAGS="-L${SUDOKU_LIBRARY_PATH} -lsudoku" go build -o ./build/for-go
# GOOS=windows GOARCH=amd64
# GOOS=linux GOARCH=amd64
# GOOS=darwin GOARCH=amd64

run:
	LD_LIBRARY_PATH=${SUDOKU_LIBRARY_PATH} ./build/for-go 0<${PROJECT_DIR}/data/1.sudoku

clean:
	rm -f ./build/for-go
