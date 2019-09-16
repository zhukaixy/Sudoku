cmake_minimum_required(VERSION 3.0)
project(sudokujni)
include_directories(/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/JavaVM.framework/Headers)
# JavaHeader=-I/System/Library/Frameworks/JavaVM.framework/Headers
include_directories(../../../include)
link_directories("../../../buildXcode/sudoku")
add_library(${PROJECT_NAME} MODULE SudokuLib.c)
target_link_libraries(${PROJECT_NAME} sudoku)
