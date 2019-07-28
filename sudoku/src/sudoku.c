#include <stdlib.h>

#define SUDOKU_CORE // for windows dllimport
#include <sudoku.h>
#include <sudodef.h>

SUDOKU_API sudoku* CreateSudoku(sudokuReadData readData, sudokuWriteData writeData) {
  sudoku* sudo = (sudoku*)malloc(sizeof(struct sudoku));
  if (sudo == NULL) {
    return NULL;
  }
  sudo->readData = readData;
  sudo->writeData = writeData;
  readAllInitialData(sudo);
  return sudo;
}
void readAllInitialData(sudoku* sudo) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      sudo->sudoData[i][j][0] = sudo->readData(i + 1, j + 1);
    }
  }
}

SUDOKU_API void SudokuReload(sudoku* sudo, sudokuReadData readData, sudokuWriteData writeData) {
  sudo->readData = readData;
  sudo->writeData = writeData;
}

SUDOKU_API bool SudokuVerification(sudoku* sudo) {
}

SUDOKU_API void SudokuCalculateOne(sudoku* sudo) {
}

SUDOKU_API void SudokuCalculateAll(sudoku* sudo) {
}
