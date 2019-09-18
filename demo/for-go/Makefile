.PHONY: for-go run clean

ARCH=$(shell uname -s)
MAKEFILE_DIR=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PROJECT_DIR=$(patsubst %/demo/for-go/,%,$(MAKEFILE_DIR))

ifeq ($(ARCH), Darwin)
MAKE_LIBRARY_PATH=$(PROJECT_DIR)/buildXcode/sudoku/Debug
endif
ifeq ($(ARCH), Linux)
MAKE_LIBRARY_PATH=$(PROJECT_DIR)/build/sudoku/
endif

for-go:
	LIBRARY_PATH=${MAKE_LIBRARY_PATH} go build -o $(MAKEFILE_DIR)/build/for-go
# GOOS=windows GOARCH=amd64
# GOOS=linux GOARCH=amd64
# GOOS=darwin GOARCH=amd64

run:
	LD_LIBRARY_PATH=${MAKE_LIBRARY_PATH} $(MAKEFILE_DIR)/build/for-go $(PROJECT_DIR)/data/1.sudoku

clean:
	rm -f ./build/for-go
