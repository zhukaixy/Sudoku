#ifndef sudodef_h
#define sudodef_h

#include <sudoku.h>

struct sudoku {
  int sudoData[9][9][10];
  sudokuRealloc realloc;
  sudokuReadData readData;
  sudokuWriteData writeData;
};

void readAllInitialData(sudoku* sudo);

#endif
