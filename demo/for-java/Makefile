.PHONY: for-java jnilib header run clean

ARCH=$(shell uname -s)
MAKEFILE_DIR=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PROJECT_DIR=$(patsubst %/demo/for-java/,%,$(MAKEFILE_DIR))

ifeq ($(ARCH), Darwin)
JavaHeader=-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/JavaVM.framework/Headers
# JavaHeader=-I/System/Library/Frameworks/JavaVM.framework/Headers
SudokuLib=-L$(PROJECT_DIR)/buildXcode/sudoku/Debug
LibRuntimePath=-Wl,-rpath $(PROJECT_DIR)/buildXcode/sudoku/Debug
LibraryName=libsudokujni.jnilib
endif

ifeq ($(ARCH), Linux)
JavaHeader=-I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
SudokuLib=-L$(PROJECT_DIR)/build/sudoku
LibRuntimePath=-Wl,-rpath $(PROJECT_DIR)/build/sudoku
LibraryName=libsudokujni.so
endif

SudokuHeader=-I$(PROJECT_DIR)/include

for-java: libsudokujni SudokuLib.class BoolMatrix.class Sudoku.class Main.class

libsudokujni: jni/SudokuLib.c jni/SudokuLib.h
	test -d build || mkdir build
	gcc  -o build/${LibraryName} -dynamiclib -shared -fPIC ${JavaHeader} ${SudokuHeader} ${SudokuLib} ${LibRuntimePath} jni/SudokuLib.c -lsudoku

%.class: %.java
	javac -d build -classpath build $^

header: jni/SudokuLib.h

jni/SudokuLib.h: SudokuLib.java
	javac SudokuLib.java
	javah -d jni SudokuLib

run:
	java -Djava.library.path=${MAKEFILE_DIR}build -classpath ${MAKEFILE_DIR}build Main 0<$(PROJECT_DIR)/data/1.sudoku

clean:
	rm -rf build/*
