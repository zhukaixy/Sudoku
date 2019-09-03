#include <stdio.h>
#include <stdbool.h>

#include <sudoku.h>

// clang-format off
// int board[81] = {
//   0,6,0,5,9,3,0,0,0,
//   9,0,1,0,0,0,5,0,0,
//   0,3,0,4,0,0,0,9,0,
//   1,0,8,0,2,0,0,0,4,
//   4,0,0,3,0,9,0,0,1,
//   2,0,0,0,1,0,6,0,9,
//   0,8,0,0,0,6,0,2,0,
//   0,0,4,0,0,0,8,0,7,
//   0,0,0,7,8,5,0,1,0
// };
// int board[81] = {
//   8,0,0,0,0,0,0,0,0,
//   0,0,3,6,0,0,0,0,0,
//   0,7,0,0,9,0,2,0,0,
//   0,5,0,0,0,7,0,0,0,
//   0,0,0,0,4,0,7,0,0,
//   0,0,0,1,0,5,0,3,0,
//   0,0,1,0,0,0,0,6,8,
//   0,0,8,5,0,0,0,1,0,
//   0,9,0,0,0,0,4,0,0
// };
// int board[81] = {
//   8,0,0,0,0,0,0,0,0,
//   0,0,3,6,0,0,0,0,0,
//   0,7,0,0,9,0,2,0,0,
//   0,5,0,0,0,7,0,0,0,
//   0,0,0,0,4,5,7,0,0,
//   0,0,0,1,0,0,0,3,0,
//   0,0,1,0,0,0,0,6,8,
//   0,0,8,5,0,0,0,1,0,
//   0,9,0,0,0,0,4,0,0
// };
int board[81] = {
    8, 0, 0,  0, 0, 0,  0, 0, 0,
    0, 0, 3,  6, 0, 0,  0, 0, 0,
    0, 7, 0,  0, 9, 0,  2, 0, 0,
    
    0, 5, 0,  0, 7, 0,  0, 0, 0,
    0, 0, 0,  0, 4, 5,  7, 0, 0,
    0, 0, 0,  1, 0, 0,  0, 3, 0,
    
    0, 0, 1,  0, 0, 0,  0, 6, 8,
    0, 0, 8,  5, 0, 0,  0, 1, 0,
    0, 9, 0,  0, 0, 0,  4, 0, 0
};
// clang-format on

// row and col are in [1, 9]
static int read_board(int row, int col) {
  return board[(row - 1) * 9 + col - 1];
}
static void write_board(int row, int col, int value, SolveType type) {
  (void)type;
  board[(row - 1) * 9 + col - 1] = value;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  Sudoku* sudo = CreateSudoku(read_board, write_board);
  char buffer[RESULT_BUFFER_SIZE];
  MakeResultString(sudo, buffer, RESULT_BUFFER_SIZE);
  printf("Sudoku Puzzle:\n%s", buffer);
  int cnt = GetKnownCount(sudo);
  printf("Sudoku Known Count: %d\n", cnt);
  int num = CalculateSudokuAll(sudo, true, NULL, NULL);
  printf("All Answer Count: %d\n", num);
  MakeResultString(sudo, buffer, RESULT_BUFFER_SIZE);
  printf("One of it:\n%s", buffer);
  int status = VerifySudoku(sudo);
  printf("Verify: %s\n", status ? "True" : "False");
  DestroySudoku(sudo);
  return 0;
}
