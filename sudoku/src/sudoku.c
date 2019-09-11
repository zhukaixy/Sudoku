#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sudoku.h>
#include <sudodef.h>
#include <methods.h>
#include <sudomat.h>
#include <sudostep.h>

SUDOKU_API Sudoku*
CreateSudoku(SudokuReadData readData, SudokuWriteData writeData, SolveProcessCallback procCallback, void* data) {
  if (readData == NULL || writeData == NULL) {
    return NULL;
  }
  Sudoku* sudo = (Sudoku*)malloc(sizeof(Sudoku));
  if (sudo == NULL) {
    return NULL;
  }
  memset(sudo, 0, sizeof(Sudoku));
  sudo->readData = readData;
  sudo->writeData = writeData;
  sudo->procCallback = procCallback;
  sudo->dataIO = data;
  sudo->hasWriteData = false;
  sudo->unknownCount = 0;
  sudo->dancing = false;
  sudo->ansCallback = NULL;
  sudo->ansCount = 0;
  initial_all(sudo);
  return sudo;
}

SUDOKU_API void DestroySudoku(Sudoku* sudo) {
  if (sudo == NULL) {
    return;
  }
  free(sudo);
}

SUDOKU_API bool VerifySudokuBoard(const int* board) {
  if (grids_has_zero(board)) {
    return false;
  }
  if (row_has_repeat_element(board)) {
    return false;
  }
  if (col_has_repeat_element(board)) {
    return false;
  }
  if (block_has_repeat_element(board)) {
    return false;
  }
  return true;
}

SUDOKU_API bool VerifySudoku(Sudoku* sudo) {
  int board[81];
  memset(board, 0, 81);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int index = i * 9 + j;
      board[index] = sudo->sudoData[i][j][0];
    }
  }
  return VerifySudokuBoard(board);
}

SUDOKU_API int GetKnownCount(Sudoku* sudo) {
  return 81 - sudo->unknownCount;
}

SUDOKU_API void MakeResultString(Sudoku* sudo, char* buffer, int size) {
  memset(buffer, 0, size);
  if (size < RESULT_BUFFER_SIZE) {
    return;
  }
  int writeCount = 0;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      sprintf(buffer + writeCount, "%d ", sudo->sudoData[i][j][0]);
      writeCount += 2;
      if (j == 2 || j == 5) {
        sprintf(buffer + writeCount, " ");
        writeCount += 1;
      }
    }
    sprintf(buffer + writeCount, "\n");
    writeCount += 1;
    if (i == 2 || i == 5) {
      sprintf(buffer + writeCount, "\n");
      writeCount += 1;
    }
  }
  assert(writeCount == RESULT_BUFFER_SIZE - 1);
}

SUDOKU_API int CalculateSudokuAll(Sudoku* sudo, bool dancing, SudokuAnswerCallback cb, void* data) {
  sudo->dancing = dancing;
  sudo->ansCallback = cb;
  sudo->data = data;
  sudo->ansCount = 0;
  if (sudo->dancing) {
    calculate_with_dancing(sudo);
  } else {
    calculate_step_by_step(sudo);
  }
  return sudo->ansCount;
}
