#ifndef _METHODS_H_
#define _METHODS_H_

#include <sudodef.h>

// ============================================================================
#pragma mark Index transform
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
#pragma mark Find answer
// ============================================================================
#define FIND_ONE_GRID_ANSWER(sudo, row, col, value, type) \
  { \
    sudo->improveCount++; \
    sudo->sudoData[row][col][0] = value; \
    sudo->writeData(sudo->dataIO, row + 1, col + 1, value, type); \
    remove_grid_posibility(sudo, row, col); \
  }
// ============================================================================
#pragma mark 2 grid with 2 posibility
// ============================================================================
#define ROW_2_GRID_WITH_2_POSIBILITY(proc, g1x, g1y, g2x, g2y, v1, v2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Row2GridWith2Posibility; \
    proc.gridOneX = (g1x) + 1; \
    proc.gridOneY = (g1y) + 1; \
    proc.gridTwoX = (g2x) + 1; \
    proc.gridTwoY = (g2y) + 1; \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
#define COL_2_GRID_WITH_2_POSIBILITY(proc, g1x, g1y, g2x, g2y, v1, v2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Col2GridWith2Posibility; \
    proc.gridOneX = (g1x) + 1; \
    proc.gridOneY = (g1y) + 1; \
    proc.gridTwoX = (g2x) + 1; \
    proc.gridTwoY = (g2y) + 1; \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
#define BLOCK_2_GRID_WITH_2_POSIBILITY(proc, g1x, g1y, g2x, g2y, v1, v2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Block2GridWith2Posibility; \
    proc.gridOneX = (g1x) + 1; \
    proc.gridOneY = (g1y) + 1; \
    proc.gridTwoX = (g2x) + 1; \
    proc.gridTwoY = (g2y) + 1; \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
// ============================================================================
#pragma mark 3 grid with 3 posibility
// ============================================================================
#define ROW_3_GRID_WITH_3_POSIBILITY(proc, g1x, g1y, g2x, g2y, g3x, g3y, v1, v2, v3) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Row3GridWith3Posibility; \
    proc.gridOneX = (g1x) + 1; \
    proc.gridOneY = (g1y) + 1; \
    proc.gridTwoX = (g2x) + 1; \
    proc.gridTwoY = (g2y) + 1; \
    proc.gridThreeX = (g3x) + 1; \
    proc.gridThreeY = (g3y) + 1; \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
    proc.numberThree = (v3); \
  }
#define COL_3_GRID_WITH_3_POSIBILITY(proc, g1x, g1y, g2x, g2y, g3x, g3y, v1, v2, v3) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Col3GridWith3Posibility; \
    proc.gridOneX = (g1x) + 1; \
    proc.gridOneY = (g1y) + 1; \
    proc.gridTwoX = (g2x) + 1; \
    proc.gridTwoY = (g2y) + 1; \
    proc.gridThreeX = (g3x) + 1; \
    proc.gridThreeY = (g3y) + 1; \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
    proc.numberThree = (v3); \
  }
#define BLOCK_3_GRID_WITH_3_POSIBILITY(proc, g1x, g1y, g2x, g2y, g3x, g3y, v1, v2, v3) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Block3GridWith3Posibility; \
    proc.gridOneX = (g1x) + 1; \
    proc.gridOneY = (g1y) + 1; \
    proc.gridTwoX = (g2x) + 1; \
    proc.gridTwoY = (g2y) + 1; \
    proc.gridThreeX = (g3x) + 1; \
    proc.gridThreeY = (g3y) + 1; \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
    proc.numberThree = (v3); \
  }
// ============================================================================
#pragma mark 2 number in 2 grid
// ============================================================================
#define ROW_2_NUMBER_IN_2_GRID(proc, v1, v2, g1x, g1y, g2x, g2y) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Row2NumberIn2Grid; \
    proc.gridOneX = (g1x) + 1; \
    proc.gridOneY = (g1y) + 1; \
    proc.gridTwoX = (g2x) + 1; \
    proc.gridTwoY = (g2y) + 1; \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
#define COL_2_NUMBER_IN_2_GRID(proc, v1, v2, g1x, g1y, g2x, g2y) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Col2NumberIn2Grid; \
    proc.gridOneX = (g1x) + 1; \
    proc.gridOneY = (g1y) + 1; \
    proc.gridTwoX = (g2x) + 1; \
    proc.gridTwoY = (g2y) + 1; \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
#define BLOCK_2_NUMBER_IN_2_GRID(proc, v1, v2, g1x, g1y, g2x, g2y) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Block2NumberIn2Grid; \
    proc.gridOneX = (g1x) + 1; \
    proc.gridOneY = (g1y) + 1; \
    proc.gridTwoX = (g2x) + 1; \
    proc.gridTwoY = (g2y) + 1; \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
  }
// ============================================================================
#pragma mark 3 number in 3 grid
// ============================================================================
#define ROW_3_NUMBER_IN_3_GRID(proc, v1, v2, v3, g1x, g1y, g2x, g2y, g3x, g3y) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Row3NumberIn3Grid; \
    proc.gridOneX = (g1x) + 1; \
    proc.gridOneY = (g1y) + 1; \
    proc.gridTwoX = (g2x) + 1; \
    proc.gridTwoY = (g2y) + 1; \
    proc.gridThreeX = (g3x) + 1; \
    proc.gridThreeY = (g3y) + 1; \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
    proc.numberThree = (v3); \
  }
#define COL_3_NUMBER_IN_3_GRID(proc, v1, v2, v3, g1x, g1y, g2x, g2y, g3x, g3y) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Col3NumberIn3Grid; \
    proc.gridOneX = (g1x) + 1; \
    proc.gridOneY = (g1y) + 1; \
    proc.gridTwoX = (g2x) + 1; \
    proc.gridTwoY = (g2y) + 1; \
    proc.gridThreeX = (g3x) + 1; \
    proc.gridThreeY = (g3y) + 1; \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
    proc.numberThree = (v3); \
  }
#define BLOCK_3_NUMBER_IN_3_GRID(proc, v1, v2, v3, g1x, g1y, g2x, g2y, g3x, g3y) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = Block3NumberIn3Grid; \
    proc.gridOneX = (g1x) + 1; \
    proc.gridOneY = (g1y) + 1; \
    proc.gridTwoX = (g2x) + 1; \
    proc.gridTwoY = (g2y) + 1; \
    proc.gridThreeX = (g3x) + 1; \
    proc.gridThreeY = (g3y) + 1; \
    proc.numberOne = (v1); \
    proc.numberTwo = (v2); \
    proc.numberThree = (v3); \
  }
// ============================================================================
#pragma mark Block number in row/col
// ============================================================================
#define IN_BLOCK_NUMBER_IN_ONE_ROW(proc, pRow, pCol, value, row) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = InBlockNumberInOneRow; \
    proc.panelRow = (pRow) + 1; \
    proc.panelCol = (pCol) + 1; \
    proc.number = (value); \
    proc.line = (row) + 1; \
  }
#define IN_BLOCK_NUMBER_IN_ONE_COL(proc, pRow, pCol, value, col) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = InBlockNumberInOneCol; \
    proc.panelRow = (pRow) + 1; \
    proc.panelCol = (pCol) + 1; \
    proc.number = (value); \
    proc.line = (col) + 1; \
  }
// ============================================================================
#pragma mark Row/col number in block
// ============================================================================
#define IN_ROW_NUMBER_IN_BLOCK(proc, row, value, pRow, pCol) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = InRowNumberInBlock; \
    proc.panelRow = (pRow) + 1; \
    proc.panelCol = (pCol) + 1; \
    proc.number = (value); \
    proc.line = (row) + 1; \
  }
#define IN_COL_NUMBER_IN_BLOCK(proc, col, value, pRow, pCol) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = InColNumberInBlock; \
    proc.panelRow = (pRow) + 1; \
    proc.panelCol = (pCol) + 1; \
    proc.number = (value); \
    proc.line = (col) + 1; \
  }
// ============================================================================
#pragma mark 2 row/col one number in 2 col/row
// ============================================================================
#define TWO_ROW_ONE_NUMBER_IN_TWO_COL(proc, r1, r2, value, c1, c2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = TwoRowOneNumberInTwoCol; \
    proc.rowOne = (r1) + 1; \
    proc.rowTwo = (r2) + 1; \
    proc.number = (value); \
    proc.colOne = (c1) + 1; \
    proc.colTwo = (c2) + 1; \
  }
#define TWO_COL_ONE_NUMBER_IN_TWO_ROW(proc, c1, c2, value, r1, r2) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = TwoColOneNumberInTwoRow; \
    proc.rowOne = (r1) + 1; \
    proc.rowTwo = (r2) + 1; \
    proc.number = (value); \
    proc.colOne = (c1) + 1; \
    proc.colTwo = (c2) + 1; \
  }
// ============================================================================
#pragma mark 3 row/col one number in 3 col/row
// ============================================================================
#define THREE_ROW_ONE_NUMBER_IN_THREE_COL(proc, r1, r2, r3, value, c1, c2, c3) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = ThreeRowOneNumberInThreeCol; \
    proc.rowOne = (r1) + 1; \
    proc.rowTwo = (r2) + 1; \
    proc.rowThree = (r3) + 1; \
    proc.number = (value); \
    proc.colOne = (c1) + 1; \
    proc.colTwo = (c2) + 1; \
    proc.colThree = (c3) + 1; \
  }
#define THREE_COL_ONE_NUMBER_IN_THREE_ROW(proc, c1, c2, c3, value, r1, r2, r3) \
  { \
    memset(&proc, 0, sizeof(SolveProcedure)); \
    proc.type = ThreeColOneNumberInThreeRow; \
    proc.rowOne = (r1) + 1; \
    proc.rowTwo = (r2) + 1; \
    proc.rowThree = (r3) + 1; \
    proc.number = (value); \
    proc.colOne = (c1) + 1; \
    proc.colTwo = (c2) + 1; \
    proc.colThree = (c3) + 1; \
  }
// ============================================================================
#pragma mark Function declaration
// ============================================================================

void initial_all(Sudoku* sudo);
// board has 81 element, in [0, 80]
bool grids_has_zero(const int* board);
bool row_has_repeat_element(const int* board);
bool col_has_repeat_element(const int* board);
bool block_has_repeat_element(const int* board);

void first_remove_posibility(Sudoku* sudo);
void check_all_posibility(Sudoku* sudo);

// ============================================================================

#endif
