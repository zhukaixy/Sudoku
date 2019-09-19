.PHONY: for-go run clean

ARCH=$(shell uname -s)
MAKEFILE_DIR=$(dir $(abspath $(lastword ${MAKEFILE_LIST})))
PROJECT_DIR=$(patsubst %/demo/for-go/,%,${MAKEFILE_DIR})

ifeq (${ARCH}, Darwin)
MAKE_LIBRARY_PATH=${PROJECT_DIR}/buildXcode/sudoku/Debug
endif
ifeq (${ARCH}, Linux)
MAKE_LIBRARY_PATH=${PROJECT_DIR}/build/sudoku
endif
ifeq ($(findstring CYGWIN, ${ARCH}), CYGWIN)
MAKE_LIBRARY_PATH=${PROJECT_DIR}/buildVS/install/bin
endif

for-go:
	CGO_CFLAGS=-I${PROJECT_DIR}/include CGO_LDFLAGS="-L${MAKE_LIBRARY_PATH} -lsudoku" go build -o ${MAKEFILE_DIR}build/for-go
# GOOS=windows GOARCH=amd64
# GOOS=linux GOARCH=amd64
# GOOS=darwin GOARCH=amd64

run:
	LD_LIBRARY_PATH=${MAKE_LIBRARY_PATH} ${MAKEFILE_DIR}build/for-go 0<${PROJECT_DIR}/data/1.sudoku

clean:
	rm -f ./build/for-go
