#include <string.h>

#include <sudoku.h>
#include <sudodef.h>

typedef struct SudokuToMatrix {
  Sudoku* sudo;
  int fullToIndex[9 * 9 * 4]; // Full for Design Matrix, Index for Bool Matrix
  // Matrix Design: 81*4 Rows with 9*9*9 Columns
  // [0, 80], [81, 81*2-1], [81*2, 81*3-1], [81*3, 81*4-1]
  int indexToFull[9 * 9 * 4];
  int sizeIndex;
  int allRows[9 * 9 * 9][4];
  int sizeAllRow;
} SudokuToMatrix;

static void sudoku_cb(void* data, const int* ans, int size) {
  SudokuToMatrix* sToMat = (SudokuToMatrix*)data;
  Sudoku* sudo = sToMat->sudo;
  for (int i = 0; i < size; i++) {
    int full = sToMat->indexToFull[sToMat->allRows[ans[i]][0]];
    int rowLine = sToMat->indexToFull[sToMat->allRows[ans[i]][1]];
    int row = full / 9;
    int col = full % 9;
    int value = rowLine % 9 + 1;
    sudo->sudoData[row][col][0] = value;
    if (!sudo->hasWriteData) {
      sudo->writeData(sudo->dataIO, row + 1, col + 1, value, None);
    }
  }
  sudo->hasWriteData = true;
  if (sudo->ansCallback != NULL) {
    char tmp[RESULT_BUFFER_SIZE];
    MakeResultString(sudo, tmp, RESULT_BUFFER_SIZE);
    sudo->ansCallback(sudo->data, tmp);
  }
}
const int kRow = 81, kCol = 81 * 2, kBox = 81 * 3;
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
  SudokuToMatrix sToMat;
  memset(&sToMat, 0, sizeof(SudokuToMatrix));
  sToMat.sudo = sudo;

  sToMat.sizeIndex = 0;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (sudo->sudoData[i][j][0] == 0) {
        int index = i * 9 + j;
        sToMat.indexToFull[sToMat.sizeIndex] = index;
        sToMat.fullToIndex[index] = sToMat.sizeIndex;
        sToMat.sizeIndex++;
      }
    }
  }

  bool rows[9][10] = {{false}}; // does the row has that value
  bool cols[9][10] = {{false}}; // does the column has that value
  bool boxes[9][10] = {{false}}; // does the box has that value
  for (int row = 0; row < 9; row++) { // for all grids
    for (int col = 0; col < 9; col++) {
      int box = row / 3 * 3 + col / 3;
      int val = sudo->sudoData[row][col][0];
      rows[row][val] = true; // the row 'row' has the value 'val'
      cols[col][val] = true;
      boxes[box][val] = true;
    }
  }

  for (int i = 0; i < 9; i++) {
    for (int v = 1; v < 10; v++) {
      if (rows[i][v] == false) {
        int full = get_row_col(i, v);
        sToMat.indexToFull[sToMat.sizeIndex] = full;
        sToMat.fullToIndex[full] = sToMat.sizeIndex;
        sToMat.sizeIndex++;
      }
      if (cols[i][v] == false) {
        int full = get_col_col(i, v);
        sToMat.indexToFull[sToMat.sizeIndex] = full;
        sToMat.fullToIndex[full] = sToMat.sizeIndex;
        sToMat.sizeIndex++;
      }
      if (boxes[i][v] == false) {
        int full = get_box_col(i, v);
        sToMat.indexToFull[sToMat.sizeIndex] = full;
        sToMat.fullToIndex[full] = sToMat.sizeIndex;
        sToMat.sizeIndex++;
      }
    }
  }

  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (sudo->sudoData[row][col][0] == 0) {
        int index = row * 9 + col;
        int box = row / 3 * 3 + col / 3;
        for (int v = 1; v < 10; v++) {
          if (rows[row][v] == false && cols[col][v] == false && boxes[box][v] == false) {
            sToMat.allRows[sToMat.sizeAllRow][0] = sToMat.fullToIndex[index];
            sToMat.allRows[sToMat.sizeAllRow][1] = sToMat.fullToIndex[get_row_col(row, v)];
            sToMat.allRows[sToMat.sizeAllRow][2] = sToMat.fullToIndex[get_col_col(col, v)];
            sToMat.allRows[sToMat.sizeAllRow][3] = sToMat.fullToIndex[get_box_col(box, v)];
            sToMat.sizeAllRow++;
          }
        }
      }
    }
  }

  BoolMatrix* mat = CreateBoolMatrix(sToMat.sizeAllRow, sToMat.sizeIndex, sToMat.sizeAllRow * 4);
  for (int i = 0; i < sToMat.sizeAllRow; i++) {
    SetMatrixRowData(mat, sToMat.allRows[i], 4);
  }
  int num = DancingLinks(mat, false, sudoku_cb, (void*)&sToMat);
  DestroyBoolMatrix(mat);

  sudo->ansCount = num;
}
