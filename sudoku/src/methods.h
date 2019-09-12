#ifndef _METHODS_H_
#define _METHODS_H_

#include <sudodef.h>

// ============================================================================
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
// ============================================================================
#define FIND_ONE_GRID_ANSWER(sudo, row, col, value, type) \
  { \
    sudo->improveCount++; \
    sudo->sudoData[row][col][0] = value; \
    sudo->writeData(sudo->dataIO, row + 1, col + 1, value, type); \
    remove_grid_posibility(sudo, row, col); \
  }
// ============================================================================
#define ROW_2_GRID_WITH_2_POSIBILITY(proc, g1x, g1y, g2x, g2y, v1, v2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Row2GridWith2Posibility; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
#define COL_2_GRID_WITH_2_POSIBILITY(proc, g1x, g1y, g2x, g2y, v1, v2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Col2GridWith2Posibility; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
#define BLOCK_2_GRID_WITH_2_POSIBILITY(proc, g1x, g1y, g2x, g2y, v1, v2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Block2GridWith2Posibility; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
// ============================================================================
#define ROW_3_GRID_WITH_3_POSIBILITY(proc, g1x, g1y, g2x, g2y, g3x, g3y, v1, v2, v3) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Row3GridWith3Posibility; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.gridThreeX = (g3x); \
    proc.gridThreeY = (g3y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
    proc.numberThree = (v3); \
  }
#define COL_3_GRID_WITH_3_POSIBILITY(proc, g1x, g1y, g2x, g2y, g3x, g3y, v1, v2, v3) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Col3GridWith3Posibility; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.gridThreeX = (g3x); \
    proc.gridThreeY = (g3y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
    proc.numberThree = (v3); \
  }
#define BLOCK_3_GRID_WITH_3_POSIBILITY(proc, g1x, g1y, g2x, g2y, g3x, g3y, v1, v2, v3) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Block3GridWith3Posibility; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.gridThreeX = (g3x); \
    proc.gridThreeY = (g3y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
    proc.numberThree = (v3); \
  }
// ============================================================================
#define ROW_2_NUMBER_IN_2_GRID(proc, v1, v2, g1x, g1y, g2x, g2y) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Row2NumberIn2Grid; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
#define COL_2_NUMBER_IN_2_GRID(proc, v1, v2, g1x, g1y, g2x, g2y) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Col2NumberIn2Grid; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
#define BLOCK_2_NUMBER_IN_2_GRID(proc, v1, v2, g1x, g1y, g2x, g2y) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Block2NumberIn2Grid; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
// ============================================================================
#define ROW_3_NUMBER_IN_3_GRID(proc, v1, v2, v3, g1x, g1y, g2x, g2y, g3x, g3y) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Row3NumberIn3Grid; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.gridThreeX = (g3x); \
    proc.gridThreeY = (g3y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
    proc.numberThree = (v3); \
  }
#define COL_3_NUMBER_IN_3_GRID(proc, v1, v2, v3, g1x, g1y, g2x, g2y, g3x, g3y) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Col3NumberIn3Grid; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.gridThreeX = (g3x); \
    proc.gridThreeY = (g3y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
    proc.numberThree = (v3); \
  }
#define BLOCK_3_NUMBER_IN_3_GRID(proc, v1, v2, v3, g1x, g1y, g2x, g2y, g3x, g3y) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Block3NumberIn3Grid; \
    proc.gridOneX = (g1x); \
    proc.gridOneY = (g1y); \
    proc.gridTwoX = (g2x); \
    proc.gridTwoY = (g2y); \
    proc.gridThreeX = (g3x); \
    proc.gridThreeY = (g3y); \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
    proc.numberThree = (v3); \
  }
// ============================================================================
#define IN_BLOCK_NUMBER_IN_ONE_ROW(proc, pRow, pCol, value, row) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = InBlockNumberInOneRow; \
    proc.panelRow = (pRow); \
    proc.panelCol = (pCol); \
    proc.number = (value); \
    proc.line = (row); \
  }
#define IN_BLOCK_NUMBER_IN_ONE_COL(proc, pRow, pCol, value, col) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = InBlockNumberInOneCol; \
    proc.panelRow = (pRow); \
    proc.panelCol = (pCol); \
    proc.number = (value); \
    proc.line = (col); \
  }
// ============================================================================
#define IN_ROW_NUMBER_IN_BLOCK(proc, row, value, pRow, pCol) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = InRowNumberInBlock; \
    proc.panelRow = (pRow); \
    proc.panelCol = (pCol); \
    proc.number = (value); \
    proc.line = (row); \
  }
#define IN_COL_NUMBER_IN_BLOCK(proc, col, value, pRow, pCol) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = InColNumberInBlock; \
    proc.panelRow = (pRow); \
    proc.panelCol = (pCol); \
    proc.number = (value); \
    proc.line = (col); \
  }
// ============================================================================
#define TWO_ROW_ONE_NUMBER_IN_TWO_COL(proc, r1, r2, value, c1, c2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = TwoRowOneNumberInTwoCol; \
    proc.rowOne = (r1); \
    proc.rowTwo = (r2); \
    proc.number = (value); \
    proc.colOne = (c1); \
    proc.colTwo = (c2); \
  }
#define TWO_COL_ONE_NUMBER_IN_TWO_ROW(proc, c1, c2, value, r1, r2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = TwoColOneNumberInTwoRow; \
    proc.rowOne = (r1); \
    proc.rowTwo = (r2); \
    proc.number = (value); \
    proc.colOne = (c1); \
    proc.colTwo = (c2); \
  }
// ============================================================================

void initial_all(Sudoku* sudo);
// board has 81 element, in [0, 80]
bool grids_has_zero(const int* board);
bool row_has_repeat_element(const int* board);
bool col_has_repeat_element(const int* board);
bool block_has_repeat_element(const int* board);

void first_remove_posibility(Sudoku* sudo);
void check_all_posibility(Sudoku* sudo);

#endif
