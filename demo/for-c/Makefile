.PHONY: run

ARCH=$(shell uname -s)
MAKEFILE_DIR=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PROJECT_DIR=$(patsubst %/demo/for-c/,%,$(MAKEFILE_DIR))

ifeq (${ARCH}, Darwin)
MAKE_C_DEMO=${PROJECT_DIR}/buildXcode/demo/for-c/Debug/for-c
endif
ifeq (${ARCH}, Linux)
MAKE_C_DEMO=${PROJECT_DIR}/build/demo/for-c/for-c
endif
ifeq ($(findstring CYGWIN, ${ARCH}), CYGWIN)
MAKE_C_DEMO=${PROJECT_DIR}/buildVS/install/bin/for-c.exe
endif

run:
	${MAKE_C_DEMO} 0<${PROJECT_DIR}/data/1.sudoku
