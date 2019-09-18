.PHONY: for-go run clean

ARCH=$(shell uname -s)
MAKEFILE_DIR=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))

ifeq ($(ARCH), Darwin)
MAKE_LIBRARY_PATH=$(MAKEFILE_DIR)../../buildXcode/sudoku/Debug
endif
ifeq ($(ARCH), Linux)
MAKE_LIBRARY_PATH=../../build/sudoku/
endif

for-go:
	LIBRARY_PATH=${MAKE_LIBRARY_PATH} go build -o ./build/for-go
# GOOS=windows GOARCH=amd64
# GOOS=linux GOARCH=amd64
# GOOS=darwin GOARCH=amd64

run:
	LD_LIBRARY_PATH=${MAKE_LIBRARY_PATH} ./build/for-go ../../data/1.sudoku

clean:
	rm -f ./build/for-go
