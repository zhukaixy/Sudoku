#define SUDOKU_CORE // for windows dllimport
#include <sudoku.h>
#include <sudodef.h>

#define OneIsNullOf(PtrOne, PtrTwo, PtrThree) (PtrOne == NULL || PtrTwo == NULL || PtrThree == NULL)
SUDOKU_API sudoku* SudokuCreate(sudokuRealloc reAlloc, sudokuReadData readData, sudokuWriteData writeData) {
  if (OneIsNullOf(reAlloc, readData, writeData)) {
    return NULL;
  }
  sudoku* sudo = (sudoku*)reAlloc(NULL, sizeof(struct sudoku));
  if (sudo == NULL) {
    return NULL;
  }
  sudo->realloc = reAlloc;
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
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      for (int k = 1; k < 10; k++) {
        sudo->sudoData[i][j][k] = k;
      }
    }
  }
}
SUDOKU_API void SudokuDestroy(sudoku* sudo) {
  if (sudo == NULL) {
    return;
  }
  sudokuRealloc reAlloc = sudo->realloc;
  reAlloc(sudo, 0);
}

SUDOKU_API void SudokuReload(sudoku* sudo, sudokuReadData readData, sudokuWriteData writeData) {
  if (sudo == NULL) {
    return;
  }
  if (readData != NULL) {
    sudo->readData = readData;
    readAllInitialData(sudo);
  }
  if (writeData != NULL) {
    sudo->writeData = writeData;
  }
}

SUDOKU_API bool SudokuVerify(sudoku* sudo) {
}

SUDOKU_API void SudokuCalculateOne(sudoku* sudo) {
}

SUDOKU_API void SudokuCalculateAll(sudoku* sudo) {
}
