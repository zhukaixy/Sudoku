.PHONY: for-java jnilib header run clean

JavaHeader=-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/JavaVM.framework/Headers
# JavaHeader=-I/System/Library/Frameworks/JavaVM.framework/Headers
SudokuHeader=-I../../include
SudokuLib=-L../../buildXcode/sudoku/Debug
# SudokuLib=-L../../build/sudoku/Debug
LibRuntimePath=-Wl,-rpath ../../buildXcode/sudoku/Debug
# LibRuntimePath=-Wl,-rpath ../../build/sudoku/Debug

for-java: jnilib
	javac *.java

jnilib:
	gcc -dynamiclib -o libsudokujni.jnilib ${JavaHeader} ${SudokuHeader} ${SudokuLib} ${LibRuntimePath} jni/SudokuLib.c -lsudoku

header:
	javac SudokuLib.java
	javah -d jni SudokuLib

run:
	java Main

clean:
	rm -rf *.class *.jnilib
