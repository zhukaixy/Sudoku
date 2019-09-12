#include <string.h>

#include <sudodef.h>
#include <methods.h>

// All function begin with find_ means we have find something to do
// All function begin with check_ means check if there are something to do

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
// x and y are in the range of [0, 2]
bool one_block_has_repeat(const int* board, int x, int y) {
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
// row: [0, 8], value: [1, 9]
void remove_row_posibility(Sudoku* sudo, int row, int value) {
  for (int col = 0; col < 9; col++) {
    sudo->sudoData[row][col][value] = 0;
  }
}
// col: [0, 8], value: [1, 9]
void remove_col_posibility(Sudoku* sudo, int col, int value) {
  for (int row = 0; row < 9; row++) {
    sudo->sudoData[row][col][value] = 0;
  }
}
// row col: [0, 8]
void remove_vertical_posibility(Sudoku* sudo, int row, int col) {
  for (int value = 1; value < 10; value++) {
    sudo->sudoData[row][col][value] = 0;
  }
}
// row col: [0, 8], value: [1, 9]
void remove_block_posibility(Sudoku* sudo, int row, int col, int value) {
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
// gridRow and gridCol are in the range of [0, 8]
// sudo->sudoData[gridRow][gridCol][0] should be non zero
void remove_grid_posibility(Sudoku* sudo, int gridRow, int gridCol) {
  int value = sudo->sudoData[gridRow][gridCol][0];
  remove_row_posibility(sudo, gridRow, value);
  remove_col_posibility(sudo, gridCol, value);
  remove_vertical_posibility(sudo, gridRow, gridCol);
  remove_block_posibility(sudo, gridRow, gridCol, value);
}
// ============================================================================
// row: [0, 8], value: [1, 9]
int row_posibility_in_value(Sudoku* sudo, int row, int value) {
  int count = 0;
  for (int col = 0; col < 9; col++) {
    if (sudo->sudoData[row][col][value] != 0) {
      count++;
    }
  }
  return count;
}
// col: [0, 8], value: [1, 9]
int col_posibility_in_value(Sudoku* sudo, int col, int value) {
  int count = 0;
  for (int row = 0; row < 9; row++) {
    if (sudo->sudoData[row][col][value] != 0) {
      count++;
    }
  }
  return count;
}
// row col: [0, 8]
int vertical_posibility_in_grid(Sudoku* sudo, int row, int col) {
  int count = 0;
  for (int value = 1; value < 10; value++) {
    if (sudo->sudoData[row][col][value] != 0) {
      count++;
    }
  }
  return count;
}
// row col: [0, 8], value: [1, 9]
int block_posibility_in_value(Sudoku* sudo, int row, int col, int value) {
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
// row: [0, 8], value: [1, 9]
void find_row_only_one_answer(Sudoku* sudo, int row, int value) {
  for (int col = 0; col < 9; col++) {
    if (sudo->sudoData[row][col][value] != 0) {
      FIND_ONE_GRID_ANSWER(sudo, row, col, value, RowNumberOnlyOneGrid);
      return;
    }
  }
}
// col: [0, 8], value: [1, 9]
void find_col_only_one_answer(Sudoku* sudo, int col, int value) {
  for (int row = 0; row < 9; row++) {
    if (sudo->sudoData[row][col][value] != 0) {
      FIND_ONE_GRID_ANSWER(sudo, row, col, value, ColNumberOnlyOneGrid);
      return;
    }
  }
}
// row col: [0, 8]
void find_vertical_only_one_answer(Sudoku* sudo, int row, int col) {
  for (int value = 1; value < 10; value++) {
    if (sudo->sudoData[row][col][value] != 0) {
      FIND_ONE_GRID_ANSWER(sudo, row, col, value, GridOnlyOnePosibility);
      return;
    }
  }
}
// row col: [0, 8], value: [1, 9]
void find_block_only_one_answer(Sudoku* sudo, int row, int col, int value) {
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
// this 2 grid must has no value
// row1 col1 row2 col2: [0, 8]
bool is_2_grid_the_same_posibility(Sudoku* sudo, int row1, int col1, int row2, int col2) {
  for (int value = 1; value < 10; value++) {
    if (sudo->sudoData[row1][col1][value] != sudo->sudoData[row2][col2][value]) {
      return false;
    }
  }
  return true;
}
// row col: [0, 8], return with value1 and value2: [1, 9]
void grid_get_2_posibility(Sudoku* sudo, int row, int col, int* value1, int* value2) {
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
void grid_get_3_posibility(Sudoku* sudo, int row, int col, int* value1, int* value2, int* value3) {
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
// row col1 col2:[0, 8]
void find_row_2_grid_has_2_posibility(Sudoku* sudo, int row, int col1, int col2) {
  int value1, value2;
  grid_get_2_posibility(sudo, row, col1, &value1, &value2);
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
// col row1 row2:[0, 8]
void find_col_2_grid_has_2_posibility(Sudoku* sudo, int col, int row1, int row2) {
  int value1, value2;
  grid_get_2_posibility(sudo, row1, col, &value1, &value2);
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
//
void find_block_2_grid_has_2_posibility(Sudoku* sudo, int row1, int col1, int row2, int col2) {
  int value1, value2;
  grid_get_2_posibility(sudo, row1, col1, &value1, &value2);
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
void find_row_3_grid_has_3_posibility(Sudoku* sudo, int row, int col1, int col2, int col3, const int* mask) {
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
  for (int col = 0; col < 9; col++) {
    if (col != col1 && col != col2 && col != col3) {
      sudo->sudoData[row][col][value1] = 0;
      sudo->sudoData[row][col][value2] = 0;
      sudo->sudoData[row][col][value3] = 0;
    }
  }
  sudo->improveCount++;
  if (sudo->procCallback != NULL) {
    SolveProcedure proc;
    ROW_3_GRID_WITH_3_POSIBILITY(proc, row, col1, row, col2, row, col3, value1, value2, value3);
    sudo->procCallback(sudo->dataIO, &proc);
  }
}
void find_col_3_grid_has_3_posibility(Sudoku* sudo, int col, int row1, int row2, int row3, const int* mask) {
}
void find_block_3_grid_has_3_posibility(Sudoku* sudo,
                                        int row1,
                                        int col1,
                                        int row2,
                                        int col2,
                                        int row3,
                                        int col3,
                                        const int* mask) {
}
// ============================================================================
// row col: [0, 8], int mask[10];
void make_mask_for_vertical(Sudoku* sudo, int row, int col, int* mask) {
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
  for (int i = 1; i < 10; i++) {
    if (mask[i] == 0 && exam[i] != 0) {
      return false;
    }
  }
  return true;
}
// ============================================================================
// row col: [0, 8], int mask[10]
bool check_row_3_grid_match_mask(Sudoku* sudo, int row, int col, int* col1, int* col2, const int* mask) {
  *col1 = 0;
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
bool check_col_3_grid_match_mask(Sudoku* sudo, int col, int row, int* row1, int* row2, const int* mask) {
  *row1 = 0;
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
bool check_block_3_grid_match_mask(Sudoku* sudo,
                                   int row,
                                   int col,
                                   int* row1,
                                   int* col1,
                                   int* row2,
                                   int* col2,
                                   const int* mask) {
}
// ============================================================================
// row col: [0, 8]  sudo->sudoData[row][col][0] should be zero
void check_2_grid_with_2_Posibility(Sudoku* sudo, int row, int col) {
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
// row col: [0, 8]
void check_3_grid_with_3_Posibility(Sudoku* sudo, int row, int col) {
  int mask[10];
  make_mask_for_vertical(sudo, row, col, mask);
  for (int j = col + 1; j < 9; j++) {
    if (sudo->sudoData[row][j][0] != 0) {
      continue;
    }
    int col1, col2;
    if (check_row_3_grid_match_mask(sudo, row, j, &col1, &col2, mask)) {
      find_row_3_grid_has_3_posibility(sudo, row, j, col1, col2, mask);
    }
  }
  for (int i = row + 1; i < 9; i++) {
    if (sudo->sudoData[i][col][0] != 0) {
      continue;
    }
    int row1, row2;
    if (check_col_3_grid_match_mask(sudo, col, i, &row1, &row2, mask)) {
      find_col_3_grid_has_3_posibility(sudo, col, i, row1, row2, mask);
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
    int row1, col1, row2, col2;
    if (check_block_3_grid_match_mask(sudo, gridRow, gridCol, &row1, &col1, &row2, &col2, mask)) {
      find_block_3_grid_has_3_posibility(sudo, gridRow, gridCol, row1, col1, row2, col2, mask);
      break;
    }
  }
}
// ============================================================================
//
void check_row_2_value_in_2_grid(Sudoku* sudo, int row, int value) {
}
void check_row_3_value_in_3_grid(Sudoku* sudo, int row, int value) {
}
void check_col_2_value_in_2_grid(Sudoku* sudo, int col, int value) {
}
void check_col_3_value_in_3_grid(Sudoku* sudo, int col, int value) {
}
void check_block_2_value_in_2_grid(Sudoku* sudo, int row, int col, int value) {
}
void check_block_3_value_in_3_grid(Sudoku* sudo, int row, int col, int value) {
}
// ============================================================================
void check_row_if_all_posibility_in_block(Sudoku* sudo, int row, int value) {
}
void check_col_if_all_posibility_in_block(Sudoku* sudo, int col, int value) {
}
void check_block_if_all_posibility_in_row(Sudoku* sudo, int row, int col, int value) {
}
void check_block_if_all_posibility_in_col(Sudoku* sudo, int row, int col, int value) {
}
// ============================================================================
void check_2_row_2_posibility_in_value(Sudoku* sudo, int row, int value) {
}
void check_2_col_2_posibility_in_value(Sudoku* sudo, int col, int value) {
}
// ============================================================================
// row col: [0, 8] sudo->sudoData[row][col][0] should be zero
void check_vertical_posibility_in_grid(Sudoku* sudo, int row, int col) {
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
// row: [0, 8], value: [1, 9]
void check_row_posibility_in_value(Sudoku* sudo, int row, int value) {
  int count = row_posibility_in_value(sudo, row, value);
  if (count == 1) {
    find_row_only_one_answer(sudo, row, value);
    return;
  }
  //  if (count == 2) {
  //    check_row_2_value_in_2_grid(sudo, row, value); // find another value
  //    check_2_row_2_posibility_in_value(sudo, row, value); // find another row
  //  } else if (count == 3) {
  //    check_row_3_value_in_3_grid(sudo, row, value);
  //  }
  //  if (count <= 3) {
  //    check_row_if_all_posibility_in_block(sudo, row, value);
  //  }
}
// col: [0, 8], value: [1, 9]
void check_col_posibility_in_value(Sudoku* sudo, int col, int value) {
  int count = col_posibility_in_value(sudo, col, value);
  if (count == 1) {
    find_col_only_one_answer(sudo, col, value);
    return;
  }
  if (count == 2) {
    check_col_2_value_in_2_grid(sudo, col, value); // find another value
    check_2_col_2_posibility_in_value(sudo, col, value); // find another col
  } else if (count == 3) {
    check_col_3_value_in_3_grid(sudo, col, value);
  }
  if (count <= 3) {
    check_col_if_all_posibility_in_block(sudo, col, value);
  }
}
// row col: [0, 8], value: [1, 9]
void check_block_posibility_in_value(Sudoku* sudo, int row, int col, int value) {
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
// Main Resolve Entry

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
  //  for (int col = 0; col < 9; col++) {
  //    for (int value = 1; value < 10; value++) {
  //      check_col_posibility_in_value(sudo, col, value);
  //    }
  //  }
  //  for (int pRow = 0; pRow < 3; pRow+=3) {
  //    for (int pCol = 0; pCol < 3; pCol+=3) {
  //      for (int value = 1; value < 10; value++) {
  //        check_block_posibility_in_value(sudo, pRow, pCol, value);
  //      }
  //    }
  //  }
}
// ============================================================================
