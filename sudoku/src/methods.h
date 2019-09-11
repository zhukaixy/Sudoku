#ifndef _METHODS_H_
#define _METHODS_H_

#include <sudodef.h>

// All argument are in the range of [0, 8]
#define INDEX_GRID_TO_PANEL(gridRow, gridCol, panelRow, panelCol) \
  { \
    (panelRow) = (gridRow) / 3; \
    (panelCol) = (gridCol) / 3; \
  }

#define INDEX_GRID_TO_IN_PANEL(gridRow, gridCol, inPanelRow, inPanelCol) \
  { \
    (inPanelRow) = (gridRow) % 3; \
    (inPanelCol) = (gridCol) % 3; \
  }

#define INDEX_P_INP_TO_GRID(pR, pC, iPR, iPC, gridRow, gridCol) \
  { \
    (gridRow) = (pR)*3 + (iPR); \
    (gridCol) = (pC)*3 + (iPC); \
  }

#define ROW_TWO_GRID_WITH_TWO_POSIBILITY(proc, g1x, g1y, g2x, g2y, v1, v2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = RowTwoGridWithTwoPosibility; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
#define COL_TWO_GRID_WITH_TWO_POSIBILITY(proc, g1x, g1y, g2x, g2y, v1, v2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = ColTwoGridWithTwoPosibility; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
#define BLOCK_TWO_GRID_WITH_TWO_POSIBILITY(proc, g1x, g1y, g2x, g2y, v1, v2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = BlockTwoGridWithTwoPosibility; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }

void initial_all(Sudoku* sudo);
// board has 81 element, in [0, 80]
bool grids_has_zero(const int* board);
bool row_has_repeat_element(const int* board);
bool col_has_repeat_element(const int* board);
bool block_has_repeat_element(const int* board);

void first_remove_posibility(Sudoku* sudo);
void check_all_posibility(Sudoku* sudo);

#endif
