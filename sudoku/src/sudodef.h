#ifndef sudodef_h
#define sudodef_h

#include <sudoku.h>

// All argument are in the range of [0, 8]
#define IndexGridToPanel(gridRow, gridCol, panelRow, panelCol) \
  { \
    (panelRow) = (gridRow) / 3; \
    (panelCol) = (gridCol) / 3; \
  }

#define IndexGridToInPanel(gridRow, gridCol, inPanelRow, inPanelCol) \
  { \
    (inPanelRow) = (gridRow) % 3; \
    (inPanelCol) = (gridCol) % 3; \
  }

#define IndexPIPToGrid(pR, pC, iPR, iPC, gridRow, gridCol) \
  { \
    (gridRow) = (pR)*3 + (iPR); \
    (gridCol) = (pC)*3 + (iPC); \
  }

struct Sudoku {
  int sudoData[9][9][10];
  SudokuReadData readData;
  SudokuWriteData writeData;
  void* dataIO;
  bool hasWriteData;
  int unknownCount;
  bool dancing;
  SudokuAnswerCallback ansCallback;
  void* data;
  int ansCount;
};

void initial_all(Sudoku* sudo);
// board has 81 element, in [0, 80]
bool grids_has_zero(const int* board);
bool row_has_repeat_element(const int* board);
bool col_has_repeat_element(const int* board);
// x and y are in the range of [0, 2]
bool one_block_has_repeat(const int* board, int x, int y);
bool block_has_repeat_element(const int* board);

void first_remove_posibility(Sudoku* sudo);
void remove_grid_posibility(Sudoku* sudo, int gridRow, int gridCol);

void calculate_with_dancing(Sudoku* sudo);
void calculate_step_by_step(Sudoku* sudo);

#endif
