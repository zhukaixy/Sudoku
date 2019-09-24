.PHONY: for-java libsudokujni allclass header run clean

ARCH := $(shell uname -s)
MAKEFILE_DIR_TMP := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))
MAKEFILE_DIR := $(patsubst %/,%,${MAKEFILE_DIR_TMP})
PROJECT_DIR := $(patsubst %/demo/for-java/,%,${MAKEFILE_DIR_TMP})

SUDOKU_INCLUDE_PATH := ${PROJECT_DIR}/include
JNI_LIBRARY_PATH := ${MAKEFILE_DIR}/build

ifeq ($(ARCH), Darwin)
SUDOKU_LIBRARY_PATH := ${PROJECT_DIR}/buildXcode/sudoku/Debug

JAVA_INCLUDE_PATH := /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/JavaVM.framework/Headers
# JAVA_INCLUDE_PATH=/System/Library/Frameworks/JavaVM.framework/Headers
JAVA_INCLUDE_ARCH_PATH := .
JNI_LIBRARY_NAME := build/libsudokujni.jnilib
endif

ifeq ($(ARCH), Linux)
SUDOKU_LIBRARY_PATH := ${PROJECT_DIR}/build/sudoku

JAVA_INCLUDE_PATH := $(JAVA_HOME)/include
JAVA_INCLUDE_ARCH_PATH := $(JAVA_HOME)/include/linux
JNI_LIBRARY_NAME := build/libsudokujni.so
endif

ifeq ($(findstring CYGWIN, ${ARCH}), CYGWIN)
SUDOKU_LIBRARY_PATH := ${PROJECT_DIR}/buildVS/install/bin

JAVA_INCLUDE_PATH := $(JAVA_HOME)/include
JAVA_INCLUDE_ARCH_PATH := $(JAVA_HOME)/include/win32
JNI_LIBRARY_NAME := ${PROJECT_DIR}buildVS/install/bin/sudokujni.dll

JNI_LIBRARY_PATH := $(subst \,\\,$(shell cygpath -w -a -p ${JNI_LIBRARY_PATH}))
PROJECT_DIR := $(subst \,\\,$(shell cygpath -w -a -p ${PROJECT_DIR}))
endif

for-java: libsudokujni allclass

libsudokujni: jni/SudokuLib.c jni/SudokuLib.h
	test -d build || mkdir build
	gcc  -I${SUDOKU_INCLUDE_PATH} -I${JAVA_INCLUDE_PATH} -I${JAVA_INCLUDE_ARCH_PATH} -L${SUDOKU_LIBRARY_PATH} -L${JNI_LIBRARY_PATH} -o ${JNI_LIBRARY_NAME} -shared -fPIC -Wl,-rpath ${SUDOKU_LIBRARY_PATH} jni/SudokuLib.c -lsudoku

allclass: SudokuLib.class BoolMatrix.class Sudoku.class Main.class

%.class: %.java
	javac -d build -classpath build $^

header: jni/SudokuLib.h

jni/SudokuLib.h: SudokuLib.java
	javac SudokuLib.java
	javah -d jni SudokuLib

run:
	java -Djava.library.path=${JNI_LIBRARY_PATH} -classpath ./build Main 0<${PROJECT_DIR}/data/1.sudoku

clean:
	rm -rf ./build/*
