#include <string.h>
#include <assert.h>
#include <stdio.h>

#include <sudodef.h>
#include <methods.h>

#define ASSERT_RANGE(value, min, max) assert((value) >= (min) && (value) <= (max))

// All function begin with find_ means we have find something to do
// All function begin with check_ means check if there are something to do

#pragma mark Initial and Check sudoku
// ============================================================================
void initial_all(Sudoku* sudo) {
  sudo->unknownCount = 0;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int tmp = sudo->readData(sudo->dataIO, i + 1, j + 1);
      if (tmp == 0) {
        sudo->unknownCount++;
      }
      sudo->sudoData[i][j][0] = tmp;
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
// ============================================================================
// board has 81 element, in [0, 80]
bool grids_has_zero(const int* board) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int index = i * 9 + j;
      if (board[index] == 0) {
        return true;
      }
    }
  }
  return false;
}
bool row_has_repeat_element(const int* board) {
  int tmp[10];
  for (int i = 0; i < 9; i++) {
    memset(tmp, 0, sizeof(int) * 9);
    for (int j = 0; j < 9; j++) {
      int index = i * 9 + j;
      tmp[board[index]] = 1;
    }
    for (int j = 1; j < 10; j++) {
      if (tmp[j] == 0) {
        return true;
      }
    }
  }
  return false;
}
bool col_has_repeat_element(const int* board) {
  int tmp[10];
  for (int i = 0; i < 9; i++) {
    memset(tmp, 0, sizeof(int) * 9);
    for (int j = 0; j < 9; j++) {
      int index = i * 9 + j;
      tmp[board[index]] = 1;
    }
    for (int j = 1; j < 10; j++) {
      if (tmp[j] == 0) {
        return true;
      }
    }
  }
  return false;
}
bool one_block_has_repeat(const int* board, int x, int y) {
  ASSERT_RANGE(x, 0, 2);
  ASSERT_RANGE(y, 0, 2);
  int tmp[9];
  memset(tmp, 0, sizeof(int) * 9);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int gridX = 0;
      int gridY = 0;
      INDEX_P_INP_TO_GRID(x, y, i, j, gridX, gridY);
      int index = gridX * 9 + gridY;
      tmp[i * 3 + j] = board[index];
    }
  }
  for (int i = 0; i < 9; i++) {
    if (tmp[i] == 0) {
      return true;
    }
  }
  return false;
}
bool block_has_repeat_element(const int* board) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (one_block_has_repeat(board, i, j)) {
        return true;
      }
    }
  }
  return false;
}
// ============================================================================
#pragma mark Remove grid posibility
// ============================================================================
void remove_row_posibility(Sudoku* sudo, int row, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int col = 0; col < 9; col++) {
    sudo->sudoData[row][col][value] = 0;
  }
}
void remove_col_posibility(Sudoku* sudo, int col, int value) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int row = 0; row < 9; row++) {
    sudo->sudoData[row][col][value] = 0;
  }
}
void remove_vertical_posibility(Sudoku* sudo, int row, int col) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  for (int value = 1; value < 10; value++) {
    sudo->sudoData[row][col][value] = 0;
  }
}
void remove_block_posibility(Sudoku* sudo, int row, int col, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int pRow, pCol;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int gridX = 0;
      int gridY = 0;
      INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridX, gridY);
      sudo->sudoData[gridX][gridY][value] = 0;
    }
  }
}
void remove_grid_posibility(Sudoku* sudo, int gridRow, int gridCol) {
  assert(sudo->sudoData[gridRow][gridCol][0] != 0);
  ASSERT_RANGE(gridRow, 0, 8);
  ASSERT_RANGE(gridCol, 0, 8);
  int value = sudo->sudoData[gridRow][gridCol][0];
  remove_row_posibility(sudo, gridRow, value);
  remove_col_posibility(sudo, gridCol, value);
  remove_vertical_posibility(sudo, gridRow, gridCol);
  remove_block_posibility(sudo, gridRow, gridCol, value);
}
// ============================================================================
#pragma mark Get count for row, col, vertical and block
// ============================================================================
int row_posibility_in_value(Sudoku* sudo, int row, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int count = 0;
  for (int col = 0; col < 9; col++) {
    if (sudo->sudoData[row][col][value] != 0) {
      count++;
    }
  }
  return count;
}
int col_posibility_in_value(Sudoku* sudo, int col, int value) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int count = 0;
  for (int row = 0; row < 9; row++) {
    if (sudo->sudoData[row][col][value] != 0) {
      count++;
    }
  }
  return count;
}
int vertical_posibility_in_grid(Sudoku* sudo, int row, int col) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  int count = 0;
  for (int value = 1; value < 10; value++) {
    if (sudo->sudoData[row][col][value] != 0) {
      count++;
    }
  }
  return count;
}
int block_posibility_in_value(Sudoku* sudo, int row, int col, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int pRow, pCol;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int gridX = 0;
      int gridY = 0;
      INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridX, gridY);
      if (sudo->sudoData[gridX][gridY][value] != 0) {
        count++;
      }
    }
  }
  return count;
}
// ============================================================================
#pragma mark Find answer
// ============================================================================
void find_row_only_one_answer(Sudoku* sudo, int row, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int col = 0; col < 9; col++) {
    if (sudo->sudoData[row][col][value] != 0) {
      FIND_ONE_GRID_ANSWER(sudo, row, col, value, RowNumberOnlyOneGrid);
      return;
    }
  }
}
void find_col_only_one_answer(Sudoku* sudo, int col, int value) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int row = 0; row < 9; row++) {
    if (sudo->sudoData[row][col][value] != 0) {
      FIND_ONE_GRID_ANSWER(sudo, row, col, value, ColNumberOnlyOneGrid);
      return;
    }
  }
}
void find_vertical_only_one_answer(Sudoku* sudo, int row, int col) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  for (int value = 1; value < 10; value++) {
    if (sudo->sudoData[row][col][value] != 0) {
      FIND_ONE_GRID_ANSWER(sudo, row, col, value, GridOnlyOnePosibility);
      return;
    }
  }
}
void find_block_only_one_answer(Sudoku* sudo, int row, int col, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int pRow, pCol;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int row = 0;
      int col = 0;
      INDEX_P_INP_TO_GRID(pRow, pCol, i, j, row, col);
      if (sudo->sudoData[row][col][value] != 0) {
        FIND_ONE_GRID_ANSWER(sudo, row, col, value, BlockNumberOnlyOneGrid);
        return;
      }
    }
  }
}
// ============================================================================
#pragma mark Utility for 2 grid with 2 posibility
// ============================================================================
bool is_2_grid_the_same_posibility(Sudoku* sudo, int row1, int col1, int row2, int col2) {
  assert(sudo->sudoData[row1][col1][0] == 0);
  assert(sudo->sudoData[row2][col2][0] == 0);
  ASSERT_RANGE(row1, 0, 8);
  ASSERT_RANGE(col1, 0, 8);
  ASSERT_RANGE(row2, 0, 8);
  ASSERT_RANGE(col2, 0, 8);
  for (int value = 1; value < 10; value++) {
    if (sudo->sudoData[row1][col1][value] != sudo->sudoData[row2][col2][value]) {
      return false;
    }
  }
  return true;
}
// return with value1 and value2: [1, 9]
void grid_get_2_posibility(Sudoku* sudo, int row, int col, int* value1, int* value2) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  *value1 = 0;
  for (int value = 1; value < 10; value++) {
    if (sudo->sudoData[row][col][value] != 0) {
      if (*value1 == 0) {
        *value1 = value;
      } else {
        *value2 = value;
        return;
      }
    }
  }
}
// ============================================================================
#pragma mark Find 2 grid with 2 posibility
// ============================================================================
void find_row_2_grid_has_2_posibility(Sudoku* sudo, int row, int col1, int col2) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col1, 0, 8);
  ASSERT_RANGE(col2, 0, 8);
  int value1, value2;
  grid_get_2_posibility(sudo, row, col1, &value1, &value2);
  if (row_posibility_in_value(sudo, row, value1) == 2 && row_posibility_in_value(sudo, row, value2) == 2) {
    return;
  }
  remove_row_posibility(sudo, row, value1);
  remove_row_posibility(sudo, row, value2);
  sudo->sudoData[row][col1][value1] = value1;
  sudo->sudoData[row][col1][value2] = value2;
  sudo->sudoData[row][col2][value1] = value1;
  sudo->sudoData[row][col2][value2] = value2;
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    ROW_2_GRID_WITH_2_POSIBILITY(proc, row, col1, row, col2, value1, value2);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_col_2_grid_has_2_posibility(Sudoku* sudo, int col, int row1, int row2) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(row1, 0, 8);
  ASSERT_RANGE(row2, 0, 8);
  int value1, value2;
  grid_get_2_posibility(sudo, row1, col, &value1, &value2);
  if (col_posibility_in_value(sudo, col, value1) == 2 && col_posibility_in_value(sudo, col, value2) == 2) {
    return;
  }
  remove_col_posibility(sudo, col, value1);
  remove_col_posibility(sudo, col, value2);
  sudo->sudoData[row1][col][value1] = value1;
  sudo->sudoData[row1][col][value2] = value2;
  sudo->sudoData[row2][col][value1] = value1;
  sudo->sudoData[row2][col][value2] = value2;
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    COL_2_GRID_WITH_2_POSIBILITY(proc, row1, col, row2, col, value1, value2);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_block_2_grid_has_2_posibility(Sudoku* sudo, int row1, int col1, int row2, int col2) {
  ASSERT_RANGE(row1, 0, 8);
  ASSERT_RANGE(col1, 0, 8);
  ASSERT_RANGE(row2, 0, 8);
  ASSERT_RANGE(col2, 0, 8);
  int value1, value2;
  grid_get_2_posibility(sudo, row1, col1, &value1, &value2);
  if (block_posibility_in_value(sudo, row1, col1, value1) == 2 && block_posibility_in_value(sudo, row1, col1, value2)) {
    return;
  }
  remove_block_posibility(sudo, row1, col1, value1);
  remove_block_posibility(sudo, row1, col1, value2);
  sudo->sudoData[row1][col1][value1] = value1;
  sudo->sudoData[row1][col1][value2] = value2;
  sudo->sudoData[row2][col2][value1] = value1;
  sudo->sudoData[row2][col2][value2] = value2;
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    BLOCK_2_GRID_WITH_2_POSIBILITY(proc, row1, col1, row2, col2, value1, value2);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
// ============================================================================
#pragma mark Main check 2 grid with 2 posibility
// ============================================================================
void check_2_grid_with_2_Posibility(Sudoku* sudo, int row, int col) {
  assert(sudo->sudoData[row][col][0] == 0);
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(row, 0, 8);
  for (int j = col + 1; j < 9; j++) { // that row
    if (sudo->sudoData[row][j][0] != 0) {
      continue;
    }
    if (is_2_grid_the_same_posibility(sudo, row, col, row, j)) {
      find_row_2_grid_has_2_posibility(sudo, row, col, j);
      break;
    }
  }
  for (int i = row + 1; i < 9; i++) { // that column, so loop in row
    if (sudo->sudoData[i][col][0] != 0) {
      continue;
    }
    if (is_2_grid_the_same_posibility(sudo, row, col, i, col)) {
      find_col_2_grid_has_2_posibility(sudo, col, row, i);
      break;
    }
  }
  int pRow, pCol, i, j;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  INDEX_GRID_TO_IN_PANEL(row, col, i, j);
  int index = i * 3 + j;
  for (int k = index + 1; k < 9; k++) {
    int x = k / 3;
    int y = k % 3;
    int gridRow, gridCol;
    INDEX_P_INP_TO_GRID(pRow, pCol, x, y, gridRow, gridCol);
    if (sudo->sudoData[gridRow][gridCol][0] != 0) {
      continue;
    }
    if (is_2_grid_the_same_posibility(sudo, row, col, gridRow, gridCol)) {
      find_block_2_grid_has_2_posibility(sudo, row, col, gridRow, gridCol);
      break;
    }
  }
}
// ============================================================================
#pragma mark Utility for 3 grid with 3 posibility
// ============================================================================
// int mask[10];
void make_mask_for_vertical(Sudoku* sudo, int row, int col, int* mask) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  for (int value = 1; value < 10; value++) {
    if (sudo->sudoData[row][col][value] == 0) {
      mask[value] = 0;
    } else {
      mask[value] = 1;
    }
  }
}
// if mask[i] is zero, exam[i] should be zero when match
bool is_exam_match_mask_with_zero(const int* exam, const int* mask) {
  bool hasNotZero = false;
  for (int i = 1; i < 10; i++) {
    if (mask[i] == 0) {
      if (exam[i] != 0) {
        return false;
      }
    } else {
      if (exam[i] != 0) {
        hasNotZero = true;
      }
    }
  }
  if (!hasNotZero) {
    return false;
  }
  return true;
}
// return with value1 value2 and value3: [1, 9]
void grid_get_3_posibility(Sudoku* sudo, int row, int col, int* value1, int* value2, int* value3) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  *value1 = 0;
  *value2 = 0;
  for (int value = 1; value < 10; value++) {
    if (sudo->sudoData[row][col][value] != 0) {
      if (*value1 == 0) {
        *value1 = value;
      } else if (*value2 == 0) {
        *value2 = value;
      } else {
        *value3 = value;
        return;
      }
    }
  }
}
// ============================================================================
#pragma mark Exam 3 grid with 3 posibility
// ============================================================================
// int mask[10]
bool check_row_3_grid_match_mask(Sudoku* sudo, int row, int col, int* col1, int* col2, const int* mask) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  *col1 = 0; // find another 2 grid, so *col1 and *col2 are not 0
  for (int j = col + 1; j < 9; j++) {
    if (sudo->sudoData[row][j][0] != 0) {
      continue;
    }
    int exam[10];
    make_mask_for_vertical(sudo, row, j, exam);
    if (is_exam_match_mask_with_zero(exam, mask)) {
      if (*col1 == 0) {
        *col1 = j;
      } else {
        *col2 = j;
        return true;
      }
    }
  }
  return false;
}
// int mask[10]
bool check_col_3_grid_match_mask(Sudoku* sudo, int col, int row, int* row1, int* row2, const int* mask) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(row, 0, 8);
  *row1 = 0; // find another 2 grid, so *row1 and *row2 are not 0
  for (int i = row + 1; i < 9; i++) {
    if (sudo->sudoData[i][col][0] != 0) {
      continue;
    }
    int exam[10];
    make_mask_for_vertical(sudo, i, col, exam);
    if (is_exam_match_mask_with_zero(exam, mask)) {
      if (*row1 == 0) {
        *row1 = i;
      } else {
        *row2 = i;
        return true;
      }
    }
  }
  return false;
}
// int mask[10]
bool check_block_3_grid_match_mask(Sudoku* sudo,
                                   int row,
                                   int col,
                                   int* row1,
                                   int* col1,
                                   int* row2,
                                   int* col2,
                                   const int* mask) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  *row1 = -1; // find another 2 grid, *row1 and *row2 may be 0
  *col1 = -1;
  int pRow, pCol, i, j;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  INDEX_GRID_TO_IN_PANEL(row, col, i, j);
  int index = i * 3 + j;
  for (int k = index + 1; k < 9; k++) {
    int x = k / 3;
    int y = k % 3;
    int gridRow, gridCol;
    INDEX_P_INP_TO_GRID(pRow, pCol, x, y, gridRow, gridCol);
    if (sudo->sudoData[gridRow][gridCol][0] != 0) {
      continue;
    }
    int exam[10];
    make_mask_for_vertical(sudo, gridRow, gridCol, exam);
    if (is_exam_match_mask_with_zero(exam, mask)) {
      if (*row1 == -1 && *col1 == -1) {
        *row1 = gridRow;
        *col1 = gridCol;
      } else {
        *row2 = gridRow;
        *col2 = gridCol;
        return true;
      }
    }
  }
  return false;
}
// ============================================================================
#pragma mark Find 3 grid with 3 posibility
// ============================================================================
void find_row_3_grid_has_3_posibility(Sudoku* sudo, int row, int col1, int col2, int col3, const int* mask) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col1, 0, 8);
  ASSERT_RANGE(col2, 0, 8);
  ASSERT_RANGE(col3, 0, 8);
  int value1 = 0;
  int value2 = 0;
  int value3 = 0;
  for (int value = 1; value < 10; value++) {
    if (mask[value] == 0) {
      continue;
    }
    if (value1 == 0) {
      value1 = value;
    } else if (value2 == 0) {
      value2 = value;
    } else {
      value3 = value;
      break;
    }
  }
  assert(value1 != 0 && value2 != 0 && value3 != 0);
  bool hasImprove = false;
  for (int col = 0; col < 9; col++) {
    if (col != col1 && col != col2 && col != col3) {
      int tmp1 = sudo->sudoData[row][col][value1];
      int tmp2 = sudo->sudoData[row][col][value2];
      int tmp3 = sudo->sudoData[row][col][value3];
      if (tmp1 != 0 || tmp2 != 0 || tmp3 != 0) {
        hasImprove = true;
        sudo->sudoData[row][col][value1] = 0;
        sudo->sudoData[row][col][value2] = 0;
        sudo->sudoData[row][col][value3] = 0;
      }
    }
  }
  if (!hasImprove) {
    return;
  }
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    ROW_3_GRID_WITH_3_POSIBILITY(proc, row, col1, row, col2, row, col3, value1, value2, value3);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_col_3_grid_has_3_posibility(Sudoku* sudo, int col, int row1, int row2, int row3, const int* mask) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(row1, 0, 8);
  ASSERT_RANGE(row2, 0, 8);
  ASSERT_RANGE(row3, 0, 8);
  int value1 = 0;
  int value2 = 0;
  int value3 = 0;
  for (int value = 1; value < 10; value++) {
    if (mask[value] == 0) {
      continue;
    }
    if (value1 == 0) {
      value1 = value;
    } else if (value2 == 0) {
      value2 = value;
    } else {
      value3 = value;
      break;
    }
  }
  assert(value1 != 0 && value2 != 0 && value3 != 0);
  bool hasImprove = false;
  for (int row = 0; row < 9; row++) {
    if (row != row1 && row != row2 && row != row3) {
      int tmp1 = sudo->sudoData[row][col][value1];
      int tmp2 = sudo->sudoData[row][col][value2];
      int tmp3 = sudo->sudoData[row][col][value3];
      if (tmp1 != 0 || tmp2 != 0 || tmp3 != 0) {
        hasImprove = true;
        sudo->sudoData[row][col][value1] = 0;
        sudo->sudoData[row][col][value2] = 0;
        sudo->sudoData[row][col][value3] = 0;
      }
    }
  }
  if (!hasImprove) {
    return;
  }
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    COL_3_GRID_WITH_3_POSIBILITY(proc, row1, col, row2, col, row3, col, value1, value2, value3);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_block_3_grid_has_3_posibility(Sudoku* sudo,
                                        int row1,
                                        int col1,
                                        int row2,
                                        int col2,
                                        int row3,
                                        int col3,
                                        const int* mask) {
  ASSERT_RANGE(row1, 0, 8);
  ASSERT_RANGE(col1, 0, 8);
  ASSERT_RANGE(row2, 0, 8);
  ASSERT_RANGE(col2, 0, 8);
  ASSERT_RANGE(row3, 0, 8);
  ASSERT_RANGE(col3, 0, 8);
  int value1 = 0;
  int value2 = 0;
  int value3 = 0;
  for (int value = 1; value < 10; value++) {
    if (mask[value] == 0) {
      continue;
    }
    if (value1 == 0) {
      value1 = value;
    } else if (value2 == 0) {
      value2 = value;
    } else {
      value3 = value;
      break;
    }
  }
  assert(value1 != 0 && value2 != 0 && value3 != 0);
  bool hasImprove = false;
  int pRow, pCol;
  INDEX_GRID_TO_PANEL(row1, col1, pRow, pCol);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int gridRow, gridCol;
      INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
      if (gridRow == row1 && gridCol == col1) {
        continue;
      }
      if (gridRow == row2 && gridCol == col2) {
        continue;
      }
      if (gridRow == row3 && gridCol == col3) {
        continue;
      }
      int tmp1 = sudo->sudoData[gridRow][gridCol][value1];
      int tmp2 = sudo->sudoData[gridRow][gridCol][value2];
      int tmp3 = sudo->sudoData[gridRow][gridCol][value3];
      if (tmp1 != 0 || tmp2 != 0 || tmp3 != 0) {
        hasImprove = true;
        sudo->sudoData[gridRow][gridCol][value1] = 0;
        sudo->sudoData[gridRow][gridCol][value2] = 0;
        sudo->sudoData[gridRow][gridCol][value3] = 0;
      }
    }
  }
  if (!hasImprove) {
    return;
  }
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    BLOCK_3_GRID_WITH_3_POSIBILITY(proc, row1, col1, row2, col2, row3, col3, value1, value2, value3);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
// ============================================================================
#pragma mark Main check 3 grid with 3 posibility
// ============================================================================
void check_3_grid_with_3_Posibility(Sudoku* sudo, int row, int col) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  int mask[10];
  make_mask_for_vertical(sudo, row, col, mask);
  {
    int col1, col2;
    if (check_row_3_grid_match_mask(sudo, row, col, &col1, &col2, mask)) {
      find_row_3_grid_has_3_posibility(sudo, row, col, col1, col2, mask);
    }
  }
  {
    int row1, row2;
    if (check_col_3_grid_match_mask(sudo, col, row, &row1, &row2, mask)) {
      find_col_3_grid_has_3_posibility(sudo, col, row, row1, row2, mask);
    }
  }
  {
    int row1, col1, row2, col2;
    if (check_block_3_grid_match_mask(sudo, row, col, &row1, &col1, &row2, &col2, mask)) {
      find_block_3_grid_has_3_posibility(sudo, row, col, row1, col1, row2, col2, mask);
    }
  }
}
// ============================================================================
#pragma mark Utility for 2 value in 2 grid
// ============================================================================
bool is_row_2_value_the_same_grid(Sudoku* sudo, int row, int value1, int value2) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value1, 1, 9);
  ASSERT_RANGE(value2, 1, 9);
  for (int col = 0; col < 9; col++) {
    int tmp1 = sudo->sudoData[row][col][value1];
    int tmp2 = sudo->sudoData[row][col][value2];
    if ((tmp1 == 0 && tmp2 != 0) || (tmp1 != 0 && tmp2 == 0)) {
      return false;
    }
  }
  return true;
}
bool is_col_2_value_the_same_grid(Sudoku* sudo, int col, int value1, int value2) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value1, 1, 9);
  ASSERT_RANGE(value2, 1, 9);
  for (int row = 0; row < 9; row++) {
    int tmp1 = sudo->sudoData[row][col][value1];
    int tmp2 = sudo->sudoData[row][col][value2];
    if ((tmp1 == 0 && tmp2 != 0) || (tmp1 != 0 && tmp2 == 0)) {
      return false;
    }
  }
  return true;
}
bool is_block_2_value_the_same_grid(Sudoku* sudo, int row, int col, int value1, int value2) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value1, 1, 9);
  ASSERT_RANGE(value2, 1, 9);
  int pRow, pCol;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int gridRow, gridCol;
      INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
      int tmp1 = sudo->sudoData[gridRow][gridCol][value1];
      int tmp2 = sudo->sudoData[gridRow][gridCol][value2];
      if ((tmp1 == 0 && tmp2 != 0) || (tmp1 != 0 && tmp2 == 0)) {
        return false;
      }
    }
  }
  return true;
}
// return with col1 and col2: [0, 8]
void row_get_2_grid_in_value(Sudoku* sudo, int row, int value, int* col1, int* col2) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  *col1 = -1;
  for (int col = 0; col < 9; col++) {
    if (sudo->sudoData[row][col][value] != 0) {
      if (*col1 == -1) {
        *col1 = col;
      } else {
        *col2 = col;
        return;
      }
    }
  }
}
// return with row1 and row2: [0, 8]
void col_get_2_grid_in_value(Sudoku* sudo, int col, int value, int* row1, int* row2) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  *row1 = -1;
  for (int row = 0; row < 9; row++) {
    if (sudo->sudoData[row][col][value] != 0) {
      if (*row1 == -1) {
        *row1 = row;
      } else {
        *row2 = row;
        return;
      }
    }
  }
}
void block_get_2_grid_in_value(Sudoku* sudo, int row, int col, int value, int* row1, int* col1, int* row2, int* col2) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  *row1 = -1;
  *col1 = -1;
  int pRow, pCol;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int gridRow, gridCol;
      INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
      if (sudo->sudoData[gridRow][gridCol][value] != 0) {
        if (*row1 == -1 && *col1 == -1) {
          *row1 = gridRow;
          *col1 = gridCol;
        } else {
          *row2 = gridRow;
          *col2 = gridCol;
          return;
        }
      }
    }
  }
}
// ============================================================================
#pragma mark Find 2 value in 2 grid
// ============================================================================
void find_row_2_value_in_2_grid(Sudoku* sudo, int row, int value1, int value2) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value1, 1, 9);
  ASSERT_RANGE(value2, 1, 9);
  int col1, col2;
  row_get_2_grid_in_value(sudo, row, value1, &col1, &col2);
  if (vertical_posibility_in_grid(sudo, row, col1) == 2 && vertical_posibility_in_grid(sudo, row, col2) == 2) {
    return;
  }
  remove_vertical_posibility(sudo, row, col1);
  remove_vertical_posibility(sudo, row, col2);
  sudo->sudoData[row][col1][value1] = value1;
  sudo->sudoData[row][col1][value2] = value2;
  sudo->sudoData[row][col2][value1] = value1;
  sudo->sudoData[row][col2][value2] = value2;
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    ROW_2_NUMBER_IN_2_GRID(proc, value1, value2, row, col1, row, col2);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_col_2_value_in_2_grid(Sudoku* sudo, int col, int value1, int value2) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value1, 1, 9);
  ASSERT_RANGE(value2, 1, 9);
  int row1, row2;
  col_get_2_grid_in_value(sudo, col, value1, &row1, &row2);
  if (vertical_posibility_in_grid(sudo, row1, col) == 2 && vertical_posibility_in_grid(sudo, row1, col) == 2) {
    return;
  }
  remove_vertical_posibility(sudo, row1, col);
  remove_vertical_posibility(sudo, row2, col);
  sudo->sudoData[row1][col][value1] = value1;
  sudo->sudoData[row1][col][value2] = value2;
  sudo->sudoData[row2][col][value1] = value1;
  sudo->sudoData[row2][col][value2] = value2;
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    COL_2_NUMBER_IN_2_GRID(proc, value1, value2, row1, col, row2, col);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_block_2_value_in_2_grid(Sudoku* sudo, int row, int col, int value1, int value2) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value1, 1, 9);
  ASSERT_RANGE(value2, 1, 9);
  int row1, col1, row2, col2;
  block_get_2_grid_in_value(sudo, row, col, value1, &row1, &col1, &row2, &col2);
  if (vertical_posibility_in_grid(sudo, row1, col1) == 2 && vertical_posibility_in_grid(sudo, row2, col2) == 2) {
    return;
  }
  remove_vertical_posibility(sudo, row1, col1);
  remove_vertical_posibility(sudo, row2, col2);
  sudo->sudoData[row1][col1][value1] = value1;
  sudo->sudoData[row1][col1][value2] = value2;
  sudo->sudoData[row2][col2][value1] = value1;
  sudo->sudoData[row2][col2][value2] = value2;
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    BLOCK_2_NUMBER_IN_2_GRID(proc, value1, value2, row1, col1, row2, col2);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
// ============================================================================
#pragma mark Main check 2 value in 2 grid
// ============================================================================
void check_row_2_value_in_2_grid(Sudoku* sudo, int row, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int v = value + 1; v < 10; v++) {
    if (is_row_2_value_the_same_grid(sudo, row, value, v)) {
      find_row_2_value_in_2_grid(sudo, row, value, v);
      break;
    }
  }
}
void check_col_2_value_in_2_grid(Sudoku* sudo, int col, int value) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int v = value + 1; v < 10; v++) {
    if (is_col_2_value_the_same_grid(sudo, col, value, v)) {
      find_col_2_value_in_2_grid(sudo, col, value, v);
      break;
    }
  }
}
void check_block_2_value_in_2_grid(Sudoku* sudo, int row, int col, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int v = value + 1; v < 10; v++) {
    if (is_block_2_value_the_same_grid(sudo, row, col, value, v)) {
      find_block_2_value_in_2_grid(sudo, row, col, value, v);
      break;
    }
  }
}
// ============================================================================
#pragma mark Utility for 3 value in 3 grid
// ============================================================================
// mask 1-9, int mask[10];
void make_mask_for_row(Sudoku* sudo, int row, int value, int* mask) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int col = 0; col < 9; col++) {
    if (sudo->sudoData[row][col][value] == 0) {
      mask[col + 1] = 0;
    } else {
      mask[col + 1] = 1;
    }
  }
}
void make_mask_for_col(Sudoku* sudo, int col, int value, int* mask) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int row = 0; row < 9; row++) {
    if (sudo->sudoData[row][col][value] == 0) {
      mask[row + 1] = 0;
    } else {
      mask[row + 1] = 1;
    }
  }
}
void make_mask_for_block(Sudoku* sudo, int row, int col, int value, int* mask) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int pRow, pCol;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int index = i * 3 + j;
      int gridRow, gridCol;
      INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
      if (sudo->sudoData[gridRow][gridCol][value] == 0) {
        mask[index + 1] = 0;
      } else {
        mask[index + 1] = 1;
      }
    }
  }
}
// ============================================================================
#pragma mark Exam 3 value in 3 grid
// ============================================================================
bool check_row_3_value_match_mask(Sudoku* sudo, int row, int value, int* value1, int* value2, int* mask) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  *value1 = 0;
  for (int v = value + 1; v < 10; v++) {
    int exam[10];
    make_mask_for_row(sudo, row, v, exam);
    if (is_exam_match_mask_with_zero(exam, mask)) {
      if (*value1 == 0) {
        *value1 = v;
      } else {
        *value2 = v;
        return true;
      }
    }
  }
  return false;
}
bool check_col_3_value_match_mask(Sudoku* sudo, int col, int value, int* value1, int* value2, int* mask) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  *value1 = 0;
  for (int v = value + 1; v < 10; v++) {
    int exam[10];
    make_mask_for_col(sudo, col, v, exam);
    if (is_exam_match_mask_with_zero(exam, mask)) {
      if (*value1 == 0) {
        *value1 = v;
      } else {
        *value2 = v;
        return true;
      }
    }
  }
  return false;
}
bool check_block_3_value_match_mask(Sudoku* sudo, int row, int col, int value, int* value1, int* value2, int* mask) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  *value1 = 0;
  for (int v = value + 1; v < 10; v++) {
    int exam[10];
    make_mask_for_block(sudo, row, col, v, exam);
    if (is_exam_match_mask_with_zero(exam, mask)) {
      if (*value1 == 0) {
        *value1 = v;
      } else {
        *value2 = v;
        return true;
      }
    }
  }
  return false;
}
// ============================================================================
#pragma mark Find 3 value in 3 grid
// ============================================================================
void find_row_3_value_in_3_grid(Sudoku* sudo, int row, int value1, int value2, int value3) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value1, 1, 9);
  ASSERT_RANGE(value2, 1, 9);
  ASSERT_RANGE(value3, 1, 9);
  int col1 = -1, col2 = -1, col3 = -1;
  for (int col = 0; col < 9; col++) {
    if (sudo->sudoData[row][col][value1] != 0) {
      if (col1 == -1) {
        col1 = col;
      } else if (col2 == -1) {
        col2 = col;
      } else {
        col3 = col;
        break;
      }
    }
  }
  bool hasImprove = false;
  for (int value = 1; value < 10; value++) {
    if (value != value1 && value != value2 && value != value3) {
      int tmp1 = sudo->sudoData[row][col1][value];
      int tmp2 = sudo->sudoData[row][col2][value];
      int tmp3 = sudo->sudoData[row][col3][value];
      if (tmp1 != 0 || tmp2 != 0 || tmp3 != 0) {
        hasImprove = true;
        sudo->sudoData[row][col1][value] = 0;
        sudo->sudoData[row][col2][value] = 0;
        sudo->sudoData[row][col3][value] = 0;
      }
    }
  }
  if (!hasImprove) {
    return;
  }
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    ROW_3_NUMBER_IN_3_GRID(proc, value1, value2, value3, row, col1, row, col2, row, col3);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_col_3_value_in_3_grid(Sudoku* sudo, int col, int value1, int value2, int value3) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value1, 1, 9);
  ASSERT_RANGE(value2, 1, 9);
  ASSERT_RANGE(value3, 1, 9);
  int row1 = -1, row2 = -1, row3 = -1;
  for (int row = 0; row < 9; row++) {
    if (sudo->sudoData[row][col][value1] != 0) {
      if (row1 == -1) {
        row1 = row;
      } else if (row2 == -1) {
        row2 = row;
      } else {
        row3 = row;
        break;
      }
    }
  }
  bool hasImprove = false;
  for (int value = 1; value < 10; value++) {
    if (value != value1 && value != value2 && value != value3) {
      int tmp1 = sudo->sudoData[row1][col][value];
      int tmp2 = sudo->sudoData[row2][col][value];
      int tmp3 = sudo->sudoData[row3][col][value];
      if (tmp1 != 0 || tmp2 != 0 || tmp3 != 0) {
        hasImprove = true;
        sudo->sudoData[row1][col][value] = 0;
        sudo->sudoData[row2][col][value] = 0;
        sudo->sudoData[row3][col][value] = 0;
      }
    }
  }
  if (!hasImprove) {
    return;
  }
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    COL_3_NUMBER_IN_3_GRID(proc, value1, value2, value3, row1, col, row2, col, row3, col);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_block_3_value_in_3_grid(Sudoku* sudo, int row, int col, int value1, int value2, int value3) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value1, 1, 9);
  ASSERT_RANGE(value2, 1, 9);
  ASSERT_RANGE(value3, 1, 9);
  int row1 = -1, col1 = -1, row2 = -1, col2 = -1, row3 = -1, col3 = -1;
  int pRow, pCol;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int gridRow, gridCol;
      INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
      if (sudo->sudoData[gridRow][gridCol][value1] != 0) {
        if (row1 == -1 && col1 == -1) {
          row1 = gridRow;
          col1 = gridCol;
        } else if (row2 == -1 && col2 == -1) {
          row2 = gridRow;
          col2 = gridCol;
        } else {
          row3 = gridRow;
          col3 = gridCol;
          goto GET_ALL_GRID;
        }
      }
    }
  }
GET_ALL_GRID : {
  bool hasImprove = false;
  for (int value = 1; value < 10; value++) {
    if (value != value1 && value != value2 && value != value3) {
      int tmp1 = sudo->sudoData[row1][col1][value];
      int tmp2 = sudo->sudoData[row2][col2][value];
      int tmp3 = sudo->sudoData[row3][col3][value];
      if (tmp1 != 0 || tmp2 != 0 || tmp3 != 0) {
        hasImprove = true;
        sudo->sudoData[row1][col1][value] = 0;
        sudo->sudoData[row2][col2][value] = 0;
        sudo->sudoData[row3][col3][value] = 0;
      }
    }
  }
  if (!hasImprove) {
    return;
  }
}
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    BLOCK_3_NUMBER_IN_3_GRID(proc, value1, value2, value3, row1, col1, row2, col2, row3, col3);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
// ============================================================================
#pragma mark Main check 3 value in 3 grid
// ============================================================================
void check_row_3_value_in_3_grid(Sudoku* sudo, int row, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int mask[10];
  make_mask_for_row(sudo, row, value, mask);
  int value1, value2;
  if (check_row_3_value_match_mask(sudo, row, value, &value1, &value2, mask)) {
    find_row_3_value_in_3_grid(sudo, row, value, value1, value2);
  }
}
void check_col_3_value_in_3_grid(Sudoku* sudo, int col, int value) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int mask[10];
  make_mask_for_col(sudo, col, value, mask);
  int value1, value2;
  if (check_col_3_value_match_mask(sudo, col, value, &value1, &value2, mask)) {
    find_col_3_value_in_3_grid(sudo, col, value, value1, value2);
  }
}
void check_block_3_value_in_3_grid(Sudoku* sudo, int row, int col, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int mask[10];
  make_mask_for_block(sudo, row, col, value, mask);
  int value1, value2;
  if (check_block_3_value_match_mask(sudo, row, col, value, &value1, &value2, mask)) {
    find_block_3_value_in_3_grid(sudo, row, col, value, value1, value2);
  }
}
// ============================================================================
#pragma mark Find row col posibility in block
// ============================================================================
void find_row_all_posibility_in_block(Sudoku* sudo, int row, int col, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  bool hasImprove = false;
  int pRow, pCol;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  int x, y;
  INDEX_GRID_TO_IN_PANEL(row, col, x, y);
  (void)y;
  for (int i = 0; i < 3; i++) {
    if (i == x) {
      continue;
    }
    for (int j = 0; j < 3; j++) {
      int gridRow = 0;
      int gridCol = 0;
      INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
      if (sudo->sudoData[gridRow][gridCol][value] != 0) {
        hasImprove = true;
        sudo->sudoData[gridRow][gridCol][value] = 0;
      }
    }
  }
  if (!hasImprove) {
    return;
  }
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    IN_ROW_NUMBER_IN_BLOCK(proc, row, value, pRow, pCol)
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_col_all_posibility_in_block(Sudoku* sudo, int row, int col, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  bool hasImprove = false;
  int pRow, pCol;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  int x, y;
  INDEX_GRID_TO_IN_PANEL(row, col, x, y);
  (void)x;
  for (int j = 0; j < 3; j++) {
    if (j == y) {
      continue;
    }
    for (int i = 0; i < 3; i++) {
      int gridRow = 0;
      int gridCol = 0;
      INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
      if (sudo->sudoData[gridRow][gridCol][value] != 0) {
        hasImprove = true;
        sudo->sudoData[gridRow][gridCol][value] = 0;
      }
    }
  }
  if (!hasImprove) {
    return;
  }
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    IN_COL_NUMBER_IN_BLOCK(proc, col, value, pRow, pCol)
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
// ============================================================================
#pragma mark Main check row col posibility in block
// ============================================================================
void check_row_if_all_posibility_in_block(Sudoku* sudo, int row, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  bool inBlock1 = false;
  bool inBlock2 = false;
  bool inBlock3 = false;
  int gridCol = -1;
  for (int col = 0; col < 3; col++) {
    if (sudo->sudoData[row][col][value] != 0) {
      inBlock1 = true;
      gridCol = 0;
      break;
    }
  }
  for (int col = 3; col < 6; col++) {
    if (sudo->sudoData[row][col][value] != 0) {
      inBlock2 = true;
      gridCol = 3;
      break;
    }
  }
  for (int col = 6; col < 9; col++) {
    if (sudo->sudoData[row][col][value] != 0) {
      inBlock3 = true;
      gridCol = 6;
      break;
    }
  }
  if ((inBlock1 && !inBlock2 && !inBlock3) || (!inBlock1 && inBlock2 && !inBlock3) ||
      (!inBlock1 && !inBlock2 && inBlock3)) {
    assert(gridCol != -1);
    find_row_all_posibility_in_block(sudo, row, gridCol, value);
  }
}
void check_col_if_all_posibility_in_block(Sudoku* sudo, int col, int value) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  bool inBlock1 = false;
  bool inBlock2 = false;
  bool inBlock3 = false;
  int gridRow = -1;
  for (int row = 0; row < 3; row++) {
    if (sudo->sudoData[row][col][value] != 0) {
      inBlock1 = true;
      gridRow = 0;
      break;
    }
  }
  for (int row = 3; row < 6; row++) {
    if (sudo->sudoData[row][col][value] != 0) {
      inBlock2 = true;
      gridRow = 3;
      break;
    }
  }
  for (int row = 6; row < 9; row++) {
    if (sudo->sudoData[row][col][value] != 0) {
      inBlock3 = true;
      gridRow = 6;
      break;
    }
  }
  if ((inBlock1 && !inBlock2 && !inBlock3) || (!inBlock1 && inBlock2 && !inBlock3) ||
      (!inBlock1 && !inBlock2 && inBlock3)) {
    assert(gridRow != -1);
    find_col_all_posibility_in_block(sudo, gridRow, col, value);
  }
}
// ============================================================================
#pragma mark Find block posibility in row col
// ============================================================================
void find_block_all_posibility_in_row(Sudoku* sudo, int row, int col, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  bool hasImprove = false;
  col = col / 3 * 3;
  for (int j = 0; j < 9; j++) {
    if (j < col || j > col + 2) {
      if (sudo->sudoData[row][j][value] != 0) {
        hasImprove = true;
        sudo->sudoData[row][j][value] = 0;
      }
    }
  }
  if (!hasImprove) {
    return;
  }
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    int pRow, pCol;
    INDEX_GRID_TO_IN_PANEL(row, col, pRow, pCol);
    IN_BLOCK_NUMBER_IN_ONE_ROW(proc, pRow, pCol, value, row);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_block_all_posibility_in_col(Sudoku* sudo, int row, int col, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  bool hasImprove = false;
  row = row / 3 * 3;
  for (int i = 0; i < 9; i++) {
    if (i < row || i > row + 2) {
      if (sudo->sudoData[i][col][value] != 0) {
        hasImprove = true;
        sudo->sudoData[i][col][value] = 0;
      }
    }
  }
  if (!hasImprove) {
    return;
  }
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    int pRow, pCol;
    INDEX_GRID_TO_IN_PANEL(row, col, pRow, pCol);
    IN_BLOCK_NUMBER_IN_ONE_COL(proc, pRow, pCol, value, col);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
// ============================================================================
#pragma mark Main check block posibility in row col
// ============================================================================
void check_block_if_all_posibility_in_row(Sudoku* sudo, int row, int col, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  bool inBlock1 = false;
  bool inBlock2 = false;
  bool inBlock3 = false;
  int pRow, pCol;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  int inRow = -1;
  int i = 0;
  for (int j = 0; j < 3; j++) {
    int gridRow = 0;
    int gridCol = 0;
    INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
    if (sudo->sudoData[gridRow][gridCol][value] != 0) {
      inBlock1 = true;
      inRow = gridRow;
      break;
    }
  }
  i = 1;
  for (int j = 0; j < 3; j++) {
    int gridRow = 0;
    int gridCol = 0;
    INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
    if (sudo->sudoData[gridRow][gridCol][value] != 0) {
      inBlock2 = true;
      inRow = gridRow;
      break;
    }
  }
  i = 2;
  for (int j = 0; j < 3; j++) {
    int gridRow = 0;
    int gridCol = 0;
    INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
    if (sudo->sudoData[gridRow][gridCol][value] != 0) {
      inBlock3 = true;
      inRow = gridRow;
      break;
    }
  }
  if ((inBlock1 && !inBlock2 && !inBlock3) || (!inBlock1 && inBlock2 && !inBlock3) ||
      (!inBlock1 && !inBlock2 && inBlock3)) {
    assert(inRow != -1);
    find_block_all_posibility_in_row(sudo, inRow, col, value);
  }
}
void check_block_if_all_posibility_in_col(Sudoku* sudo, int row, int col, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  bool inBlock1 = false;
  bool inBlock2 = false;
  bool inBlock3 = false;
  int pRow, pCol;
  INDEX_GRID_TO_PANEL(row, col, pRow, pCol);
  int inCol = -1;
  int j = 0;
  for (int i = 0; i < 3; i++) {
    int gridRow = 0;
    int gridCol = 0;
    INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
    if (sudo->sudoData[gridRow][gridCol][value] != 0) {
      inBlock1 = true;
      inCol = gridCol;
      break;
    }
  }
  j = 1;
  for (int i = 0; i < 3; i++) {
    int gridRow = 0;
    int gridCol = 0;
    INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
    if (sudo->sudoData[gridRow][gridCol][value] != 0) {
      inBlock2 = true;
      inCol = gridCol;
      break;
    }
  }
  j = 2;
  for (int i = 0; i < 3; i++) {
    int gridRow = 0;
    int gridCol = 0;
    INDEX_P_INP_TO_GRID(pRow, pCol, i, j, gridRow, gridCol);
    if (sudo->sudoData[gridRow][gridCol][value] != 0) {
      inBlock3 = true;
      inCol = gridCol;
      break;
    }
  }
  if ((inBlock1 && !inBlock2 && !inBlock3) || (!inBlock1 && inBlock2 && !inBlock3) ||
      (!inBlock1 && !inBlock2 && inBlock3)) {
    assert(inCol != -1);
    find_block_all_posibility_in_col(sudo, row, inCol, value);
  }
}
// ============================================================================
#pragma mark Utility for 2 row/col 2 grid
// ============================================================================
bool is_2_row_the_same_grid_in_value(Sudoku* sudo, int row1, int row2, int value) {
  ASSERT_RANGE(row1, 0, 8);
  ASSERT_RANGE(row2, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int col = 0; col < 9; col++) {
    if (sudo->sudoData[row1][col][value] != sudo->sudoData[row2][col][value]) {
      return false;
    }
  }
  return true;
}
bool is_2_col_the_same_grid_in_value(Sudoku* sudo, int col1, int col2, int value) {
  ASSERT_RANGE(col1, 0, 8);
  ASSERT_RANGE(col2, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int row = 0; row < 9; row++) {
    if (sudo->sudoData[row][col1][value] != sudo->sudoData[row][col2][value]) {
      return false;
    }
  }
  return true;
}
// ============================================================================
#pragma mark Find 2 row/col 2 grid
// ============================================================================
void find_2_row_2_grid_in_value(Sudoku* sudo, int row1, int row2, int value) {
  ASSERT_RANGE(row1, 0, 8);
  ASSERT_RANGE(row2, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int col1, col2;
  row_get_2_grid_in_value(sudo, row1, value, &col1, &col2);
  if (col_posibility_in_value(sudo, col1, value) == 2 && col_posibility_in_value(sudo, col2, value) == 2) {
    return;
  }
  remove_col_posibility(sudo, col1, value);
  remove_col_posibility(sudo, col2, value);
  sudo->sudoData[row1][col1][value] = value;
  sudo->sudoData[row1][col2][value] = value;
  sudo->sudoData[row2][col1][value] = value;
  sudo->sudoData[row2][col2][value] = value;
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    TWO_ROW_ONE_NUMBER_IN_TWO_COL(proc, row1, row2, value, col1, col2);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_2_col_2_grid_in_value(Sudoku* sudo, int col1, int col2, int value) {
  ASSERT_RANGE(col1, 0, 8);
  ASSERT_RANGE(col2, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int row1, row2;
  col_get_2_grid_in_value(sudo, col1, value, &row1, &row2);
  if (row_posibility_in_value(sudo, row1, value) == 2 && row_posibility_in_value(sudo, row2, value) == 2) {
    return;
  }
  remove_row_posibility(sudo, row1, value);
  remove_row_posibility(sudo, row2, value);
  sudo->sudoData[row1][col1][value] = value;
  sudo->sudoData[row1][col2][value] = value;
  sudo->sudoData[row2][col1][value] = value;
  sudo->sudoData[row2][col2][value] = value;
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    TWO_COL_ONE_NUMBER_IN_TWO_ROW(proc, col1, col2, value, row1, row2);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
// ============================================================================
#pragma mark Main check 2 row/col 2 grid
// ============================================================================
void check_2_row_2_grid_in_value(Sudoku* sudo, int row, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int i = row + 1; i < 9; i++) {
    if (is_2_row_the_same_grid_in_value(sudo, row, i, value)) {
      find_2_row_2_grid_in_value(sudo, row, i, value);
      break;
    }
  }
}
void check_2_col_2_grid_in_value(Sudoku* sudo, int col, int value) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  for (int j = col + 1; j < 9; j++) {
    if (is_2_col_the_same_grid_in_value(sudo, col, j, value)) {
      find_2_col_2_grid_in_value(sudo, col, j, value);
      break;
    }
  }
}
// ============================================================================
#pragma mark Exam 3 row/col 3 grid
// ============================================================================
// int mask[10]
bool check_3_row_match_mask_in_value(Sudoku* sudo, int row, int value, int* row1, int* row2, const int* mask) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  *row1 = 0; // find another 2 grid, so *col1 and *col2 are not 0
  for (int i = row + 1; i < 9; i++) {
    int exam[10];
    make_mask_for_row(sudo, i, value, exam);
    if (is_exam_match_mask_with_zero(exam, mask)) {
      if (*row1 == 0) {
        *row1 = i;
      } else {
        *row2 = i;
        return true;
      }
    }
  }
  return false;
}
bool check_3_col_match_mask_in_value(Sudoku* sudo, int col, int value, int* col1, int* col2, const int* mask) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  *col1 = 0; // find another 2 grid, so *col1 and *col2 are not 0
  for (int j = col + 1; j < 9; j++) {
    int exam[10];
    make_mask_for_col(sudo, j, value, exam);
    if (is_exam_match_mask_with_zero(exam, mask)) {
      if (*col1 == 0) {
        *col1 = j;
      } else {
        *col2 = j;
        return true;
      }
    }
  }
  return false;
}
// ============================================================================
#pragma mark Find 3 row/col 3 grid
// ============================================================================
void find_3_row_3_grid_in_value(Sudoku* sudo, int row1, int row2, int row3, int value) {
  ASSERT_RANGE(row1, 0, 8);
  ASSERT_RANGE(row2, 0, 8);
  ASSERT_RANGE(row3, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int col1 = -1, col2 = -1, col3 = -1;
  for (int col = 0; col < 9; col++) {
    if (sudo->sudoData[row1][col][value] != 0) {
      if (col1 == -1) {
        col1 = col;
      } else if (col2 == -1) {
        col2 = col;
      } else {
        col3 = col;
        break;
      }
    }
  }
  bool hasImprove = false;
  for (int row = 0; row < 9; row++) {
    if (row != row1 && row != row2 && row != row3) {
      int tmp1 = sudo->sudoData[row][col1][value];
      int tmp2 = sudo->sudoData[row][col2][value];
      int tmp3 = sudo->sudoData[row][col3][value];
      if (tmp1 != 0 || tmp2 != 0 || tmp3 != 0) {
        hasImprove = true;
        sudo->sudoData[row][col1][value] = 0;
        sudo->sudoData[row][col2][value] = 0;
        sudo->sudoData[row][col3][value] = 0;
      }
    }
  }
  if (!hasImprove) {
    return;
  }
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    THREE_ROW_ONE_NUMBER_IN_THREE_COL(proc, row1, row2, row3, value, col1, col2, col3);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_3_col_3_grid_in_value(Sudoku* sudo, int col1, int col2, int col3, int value) {
  ASSERT_RANGE(col1, 0, 8);
  ASSERT_RANGE(col2, 0, 8);
  ASSERT_RANGE(col3, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int row1 = -1, row2 = -1, row3 = -1;
  for (int row = 0; row < 9; row++) {
    if (sudo->sudoData[row][col1][value] != 0) {
      if (row1 == -1) {
        row1 = row;
      } else if (row2 == -1) {
        row2 = row;
      } else {
        row3 = row;
        break;
      }
    }
  }
  bool hasImprove = false;
  for (int col = 0; col < 9; col++) {
    if (col != col1 && col != col2 && col != col3) {
      int tmp1 = sudo->sudoData[row1][col][value];
      int tmp2 = sudo->sudoData[row2][col][value];
      int tmp3 = sudo->sudoData[row3][col][value];
      if (tmp1 != 0 || tmp2 != 0 || tmp3 != 0) {
        hasImprove = true;
        sudo->sudoData[row1][col][value] = 0;
        sudo->sudoData[row2][col][value] = 0;
        sudo->sudoData[row3][col][value] = 0;
      }
    }
  }
  if (!hasImprove) {
    return;
  }
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    THREE_COL_ONE_NUMBER_IN_THREE_ROW(proc, col1, col2, col3, value, row1, row2, row3);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
// ============================================================================
#pragma mark Main check 3 row/col 3 grid
// ============================================================================
void check_3_row_3_grid_in_value(Sudoku* sudo, int row, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int mask[10];
  make_mask_for_row(sudo, row, value, mask);
  int row1, row2;
  if (check_3_row_match_mask_in_value(sudo, row, value, &row1, &row2, mask)) {
    find_3_row_3_grid_in_value(sudo, row, row1, row2, value);
  }
}
void check_3_col_3_grid_in_value(Sudoku* sudo, int col, int value) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int mask[10];
  make_mask_for_col(sudo, col, value, mask);
  int col1, col2;
  if (check_3_col_match_mask_in_value(sudo, col, value, &col1, &col2, mask)) {
    find_3_col_3_grid_in_value(sudo, col, col1, col2, value);
  }
}
// ============================================================================
#pragma mark Main check grid row col block posibility
// ============================================================================
void check_vertical_posibility_in_grid(Sudoku* sudo, int row, int col) {
  assert(sudo->sudoData[row][col][0] == 0);
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  int count = vertical_posibility_in_grid(sudo, row, col);
  if (count == 1) {
    find_vertical_only_one_answer(sudo, row, col);
    return;
  }
  if (count == 2) {
    check_2_grid_with_2_Posibility(sudo, row, col);
  } else if (count == 3) {
    check_3_grid_with_3_Posibility(sudo, row, col);
  }
}
void check_row_posibility_in_value(Sudoku* sudo, int row, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int count = row_posibility_in_value(sudo, row, value);
  if (count == 1) {
    find_row_only_one_answer(sudo, row, value);
    return;
  }
  if (count == 2) {
    check_row_2_value_in_2_grid(sudo, row, value); // find another value
    check_2_row_2_grid_in_value(sudo, row, value); // find another row
  } else if (count == 3) {
    check_row_3_value_in_3_grid(sudo, row, value); // find another 2 value
    check_3_row_3_grid_in_value(sudo, row, value); // find another 2 row
  }
  if (count <= 3) {
    check_row_if_all_posibility_in_block(sudo, row, value);
  }
}
void check_col_posibility_in_value(Sudoku* sudo, int col, int value) {
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int count = col_posibility_in_value(sudo, col, value);
  if (count == 1) {
    find_col_only_one_answer(sudo, col, value);
    return;
  }
  if (count == 2) {
    check_col_2_value_in_2_grid(sudo, col, value); // find another value
    check_2_col_2_grid_in_value(sudo, col, value); // find another col
  } else if (count == 3) {
    check_col_3_value_in_3_grid(sudo, col, value); // find another 2 value
    check_3_col_3_grid_in_value(sudo, col, value); // find another 2 col
  }
  if (count <= 3) {
    check_col_if_all_posibility_in_block(sudo, col, value);
  }
}
void check_block_posibility_in_value(Sudoku* sudo, int row, int col, int value) {
  ASSERT_RANGE(row, 0, 8);
  ASSERT_RANGE(col, 0, 8);
  ASSERT_RANGE(value, 1, 9);
  int count = block_posibility_in_value(sudo, row, col, value);
  if (count == 1) {
    find_block_only_one_answer(sudo, row, col, value);
    return;
  }
  if (count == 2) {
    check_block_2_value_in_2_grid(sudo, row, col, value);
  } else if (count == 3) {
    check_block_3_value_in_3_grid(sudo, row, col, value);
  }
  if (count <= 3) {
    check_block_if_all_posibility_in_row(sudo, row, col, value);
    check_block_if_all_posibility_in_col(sudo, row, col, value);
  }
}
// ============================================================================
#pragma mark Main Resolve Entry
// ============================================================================
void first_remove_posibility(Sudoku* sudo) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (sudo->sudoData[i][j][0] != 0) {
        remove_grid_posibility(sudo, i, j);
      }
    }
  }
}
void check_all_posibility(Sudoku* sudo) {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (sudo->sudoData[row][col][0] == 0) {
        check_vertical_posibility_in_grid(sudo, row, col);
      }
    }
  }
  for (int row = 0; row < 9; row++) {
    for (int value = 1; value < 10; value++) {
      check_row_posibility_in_value(sudo, row, value);
    }
  }
  for (int col = 0; col < 9; col++) {
    for (int value = 1; value < 10; value++) {
      check_col_posibility_in_value(sudo, col, value);
    }
  }
  for (int row = 0; row < 9; row += 3) {
    for (int col = 0; col < 9; col += 3) {
      for (int value = 1; value < 10; value++) {
        check_block_posibility_in_value(sudo, row, col, value);
      }
    }
  }
}
// ============================================================================
