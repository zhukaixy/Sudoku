#include <string.h>

#include <sudoku.h>
#include <sudodef.h>

// Matrix Design: 81*4 Rows with 9*9*9 Columns
// [0, 80], [81, 81*2-1], [81*2, 81*3-1], [81*3, 81*4-1]
static int indexToFull[9 * 9 * 4];
static int sizeIndex;
static int allRows[9 * 9 * 9][4];
static int sizeAllRow;
static void sudoku_cb(void* data, const int* ans, int size) {
  Sudoku* sudo = (Sudoku*)data;
  for (int i = 0; i < size; i++) {
    int full = indexToFull[allRows[ans[i]][0]];
    int rowLine = indexToFull[allRows[ans[i]][1]];
    int row = full / 9;
    int col = full % 9;
    int value = rowLine % 9 + 1;
    sudo->sudoData[row][col][0] = value;
    if (!sudo->hasWriteData) {
      sudo->writeData(row + 1, col + 1, value, None);
    }
  }
  sudo->hasWriteData = true;
  if (sudo->ansCallback != NULL) {
    char tmp[RESULT_BUFFER_SIZE];
    MakeResultString(sudo, tmp, RESULT_BUFFER_SIZE);
    sudo->ansCallback(sudo->data, tmp);
  }
}
static int kRow = 81, kCol = 81 * 2, kBox = 81 * 3;
static int get_row_col(int row, int val) { // row:[0-8] val:[1-9]
  return kRow + row * 9 + val - 1;
}
static int get_col_col(int col, int val) {
  return kCol + col * 9 + val - 1;
}
static int get_box_col(int box, int val) {
  return kBox + box * 9 + val - 1;
}
void calculate_with_dancing(Sudoku* sudo) {
  int board[81];
  memset(board, 0, sizeof(int) * 81);
  bool rows[9][10] = {{false}}; // does the row has that value
  bool cols[9][10] = {{false}}; // does the column has that value
  bool boxes[9][10] = {{false}}; // does the box has that value
  for (int row = 0; row < 9; row++) { // for all grids
    for (int col = 0; col < 9; col++) {
      int box = row / 3 * 3 + col / 3;
      int val = sudo->sudoData[row][col][0];
      board[row * 9 + col] = val;
      rows[row][val] = true; // the row 'row' has the value 'val'
      cols[col][val] = true;
      boxes[box][val] = true;
    }
  }

  sizeIndex = 0;
  int fullToIndex[9 * 9 * 4];
  memset(indexToFull, 0, 9 * 9 * 4);
  memset(fullToIndex, 0, 9 * 9 * 4);

  for (int i = 0; i < 9 * 9; i++) { // 0-80 is grids
    if (board[i] == 0) {
      indexToFull[sizeIndex] = i;
      fullToIndex[i] = sizeIndex;
      sizeIndex++;
    }
  }
  for (int i = 0; i < 9; i++) {
    for (int v = 1; v < 10; v++) {
      if (rows[i][v] == false) {
        int full = get_row_col(i, v);
        indexToFull[sizeIndex] = full;
        fullToIndex[full] = sizeIndex;
        sizeIndex++;
      }
      if (cols[i][v] == false) {
        int full = get_col_col(i, v);
        indexToFull[sizeIndex] = full;
        fullToIndex[full] = sizeIndex;
        sizeIndex++;
      }
      if (boxes[i][v] == false) {
        int full = get_box_col(i, v);
        indexToFull[sizeIndex] = full;
        fullToIndex[full] = sizeIndex;
        sizeIndex++;
      }
    }
  }
  for (int i = 0; i < 81; i++) {
    if (board[i] == 0) {
      int row = i / 9;
      int col = i % 9;
      int box = row / 3 * 3 + col / 3;
      for (int v = 1; v < 10; v++) {
        if (rows[row][v] == false && cols[col][v] == false && boxes[box][v] == false) {
          allRows[sizeAllRow][0] = fullToIndex[i];
          allRows[sizeAllRow][1] = fullToIndex[get_row_col(row, v)];
          allRows[sizeAllRow][2] = fullToIndex[get_col_col(col, v)];
          allRows[sizeAllRow][3] = fullToIndex[get_box_col(box, v)];
          sizeAllRow++;
        }
      }
    }
  }
  BoolMatrix* mat = CreateBoolMatrix(sizeAllRow, sizeIndex, sizeAllRow * 4);
  for (int i = 0; i < sizeAllRow; i++) {
    SetMatrixRowData(mat, allRows[i], 4);
  }
  int num = DancingLinks(mat, false, sudoku_cb, (void*)sudo);
  DestroyBoolMatrix(mat);
  sudo->ansCount = num;
}
