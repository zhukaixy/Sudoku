#include <sudodef.h>

void initial_all(Sudoku* sudo) {
  sudo->unknownCount = 0;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int tmp = sudo->readData(i + 1, j + 1);
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

bool grids_has_zero(Sudoku* sudo) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (sudo->sudoData[i][j][0] == 0) {
        return true;
      }
    }
  }
  return false;
}
bool row_has_repeat_element(Sudoku* sudo) {
  int tmp[10];
  for (int i = 0; i < 9; i++) {
    memset(tmp, 0, sizeof(int) * 9);
    for (int j = 0; j < 9; j++) {
      tmp[sudo->sudoData[i][j][0]] = 1;
    }
    int result = 1;
    for (int j = 1; j < 10; j++) {
      result *= tmp[j];
    }
    if (result == 0) {
      return true;
    }
  }
  return false;
}
bool col_has_repeat_element(Sudoku* sudo) {
  int tmp[10];
  for (int i = 0; i < 9; i++) {
    memset(tmp, 0, sizeof(int) * 9);
    for (int j = 0; j < 9; j++) {
      tmp[sudo->sudoData[j][i][0]] = 1;
    }
    int result = 1;
    for (int j = 1; j < 10; j++) {
      result *= tmp[j];
    }
    if (result == 0) {
      return true;
    }
  }
  return false;
}
// x and y are in the range of [0, 2]
bool one_block_has_repeat(Sudoku* sudo, int x, int y) {
  int tmp[9];
  memset(tmp, 0, sizeof(int) * 9);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int gridX = 0;
      int gridY = 0;
      IndexPIPToGrid(x, y, i, j, gridX, gridY);
      tmp[i * 3 + j] = sudo->sudoData[gridX][gridY][0];
    }
  }
  int result = 1;
  for (int i = 0; i < 9; i++) {
    result *= tmp[i];
  }
  if (result == 0) {
    return true;
  }
  return false;
}
bool block_has_repeat_element(Sudoku* sudo) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (one_block_has_repeat(sudo, i, j)) {
        return true;
      }
    }
  }
  return false;
}

void first_remove_posibility(Sudoku* sudo) {
}

// gridRow and gridCol are in the range of [0, 8]
void remove_grid_posibility(Sudoku* sudo, int gridRow, int gridCol) {
}
