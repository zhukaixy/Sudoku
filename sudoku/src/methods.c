#include <string.h>
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

// board has 81 element, in [0, 80]
bool grids_has_zero(int* board) {
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
bool row_has_repeat_element(int* board) {
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
bool col_has_repeat_element(int* board) {
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
bool one_block_has_repeat(int* board, int x, int y) {
  int tmp[9];
  memset(tmp, 0, sizeof(int) * 9);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int gridX = 0;
      int gridY = 0;
      IndexPIPToGrid(x, y, i, j, gridX, gridY);
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
bool block_has_repeat_element(int* board) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (one_block_has_repeat(board, i, j)) {
        return true;
      }
    }
  }
  return false;
}

// gridRow and gridCol are in the range of [0, 8]
// sudo->sudoData[gridRow][gridCol][0] should be non zero
void remove_grid_posibility(Sudoku* sudo, int gridRow, int gridCol) {
  int value = sudo->sudoData[gridRow][gridCol][0];
  for (int k = 0; k < 9; k++) {
    sudo->sudoData[gridRow][k][value] = 0; // that row
    sudo->sudoData[k][gridCol][value] = 0; // that col
    sudo->sudoData[gridRow][gridCol][k + 1] = 0; // that vertical cylinder
  }
  int panelRow, panelCol;
  IndexGridToPanel(gridRow, gridCol, panelRow, panelCol);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int gridX = 0;
      int gridY = 0;
      IndexPIPToGrid(panelRow, panelCol, i, j, gridX, gridY);
      sudo->sudoData[gridX][gridY][value] = 0;
    }
  }
}

void first_remove_posibility(Sudoku* sudo) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (sudo->sudoData[i][j][0] != 0) {
        remove_grid_posibility(sudo, i, j);
      }
    }
  }
}
