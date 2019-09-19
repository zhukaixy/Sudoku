.PHONY: for-java jnilib header run clean

ARCH=$(shell uname -s)
MAKEFILE_DIR=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PROJECT_DIR=$(patsubst %/demo/for-java/,%,$(MAKEFILE_DIR))

ifeq ($(ARCH), Darwin)
JavaHeader=-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/JavaVM.framework/Headers
# JavaHeader=-I/System/Library/Frameworks/JavaVM.framework/Headers
SudokuLib=-L$(PROJECT_DIR)/buildXcode/sudoku/Debug
LibRuntimePath=-Wl,-rpath $(PROJECT_DIR)/buildXcode/sudoku/Debug
endif

ifeq ($(ARCH), Linux)
JavaHeader=-I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
SudokuLib=-L$(PROJECT_DIR)/build/sudoku
LibRuntimePath=-Wl,-rpath $(PROJECT_DIR)/build/sudoku
endif

SudokuHeader=-I$(PROJECT_DIR)/include

for-java: libsudokujni.jnilib SudokuLib.class BoolMatrix.class Sudoku.class Main.class

libsudokujni.jnilib: jni/SudokuLib.c jni/SudokuLib.h
	gcc  -o $@ -dynamiclib -shared -fPIC ${JavaHeader} ${SudokuHeader} ${SudokuLib} ${LibRuntimePath} jni/SudokuLib.c -lsudoku

%.class: %.java
	javac $^

header: jni/SudokuLib.h

jni/SudokuLib.h: SudokuLib.java
	javac SudokuLib.java
	javah -d jni SudokuLib

run:
	java Main 0<$(PROJECT_DIR)/data/1.sudoku

clean:
	rm -rf *.class *.jnilib
