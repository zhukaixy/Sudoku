#ifndef _SUDO_DEF_H_
#define _SUDO_DEF_H_

#include <sudoku.h>

struct Sudoku {
  int sudoData[9][9][10]; // board for calculate
  SudokuReadData readData;
  SudokuWriteData writeData;
  SolveProcessCallback procCallback; // Only Use by Solve step by step
  void* dataIO; // for readData writeData and procCallback
  bool hasWriteData;
  int unknownCount;
  bool dancing;
  SudokuAnswerCallback ansCallback;
  void* data; // for ansCallback
  int ansCount; // answer count
  bool hasFindAnswer;
};

#endif
