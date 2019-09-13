#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <sudoku.h>

FILE* open_file_for_read(const char* path) {
  assert(path != NULL);
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    fprintf(stderr, "Error: open file %s failed\n", path);
  }
  return file;
}

bool get_sudoku_from_file(int* sudo, int size, FILE* file) {
  assert(sudo != NULL && size >= 81 && file != NULL);
  memset(sudo, 0, size);
  int count = 0;
  for (; count < 81;) {
    int c = fgetc(file);
    if (c == EOF) {
      return false;
    }
    if (c >= '0' && c <= '9') {
      sudo[count] = c - '0';
      count++;
    }
  }
  return true;
}

void display_sudoku(int* sudo) {
  assert(sudo != NULL);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int index = i * 9 + j;
      printf("%d ", sudo[index]);
      if (j == 2 || j == 5)
        printf(" ");
    }
    printf("\n");
    if (i == 2 || i == 5) {
      printf("\n");
    }
  }
}

// row and col are in [1, 9]
int read_board(void* data, int row, int col) {
  assert(row >= 1 && row <= 9 && col >= 1 && col <= 9);
  int* board = (int*)data;
  return board[(row - 1) * 9 + col - 1];
}
void write_board(void* data, int row, int col, int value, SolveType type) {
  assert(row >= 1 && row <= 9 && col >= 1 && col <= 9 && value >= 1 && value <= 9);
  int* board = (int*)data;
  board[(row - 1) * 9 + col - 1] = value;
  printf("Solve: %s row:%d column:%d value:%d\n", SolveTypeName(type), row, col, value);
}
void write_board_dancing(void* data, int row, int col, int value, SolveType type) {
  (void)type;
  assert(row >= 1 && row <= 9 && col >= 1 && col <= 9 && value >= 1 && value <= 9);
  int* board = (int*)data;
  board[(row - 1) * 9 + col - 1] = value;
}
void solve_process(void* data, SolveProcedure* proc) {
  (void)data;
  printf("Improve: %s ", ImproveTypeName(proc->type));
  switch (proc->type) {
    case DoNotImprove:
      printf("Do Not Improve\n");
      break;

    case Row2GridWith2Posibility:
    case Col2GridWith2Posibility:
    case Block2GridWith2Posibility:
      printf("gridOne: %d %d, gridTwo: %d %d, value: %d %d\n",
             proc->gridOneX,
             proc->gridOneY,
             proc->gridTwoX,
             proc->gridTwoY,
             proc->numberOne,
             proc->numberTwo);
      break;

    case Row3GridWith3Posibility:
    case Col3GridWith3Posibility:
    case Block3GridWith3Posibility:
      printf("gridOne: %d %d, gridTwo: %d %d, gridThree: %d %d, value: %d %d %d\n",
             proc->gridOneX,
             proc->gridOneY,
             proc->gridTwoX,
             proc->gridTwoY,
             proc->gridThreeX,
             proc->gridThreeY,
             proc->numberOne,
             proc->numberTwo,
             proc->numberThree);
      break;

    case Row2NumberIn2Grid:
      break;
    case Col2NumberIn2Grid:
      break;
    case Block2NumberIn2Grid:
      break;

    case Row3NumberIn3Grid:
      break;
    case Col3NumberIn3Grid:
      break;
    case Block3NumberIn3Grid:
      break;

    case InBlockNumberInOneRow:
      break;
    case InBlockNumberInOneCol:
      break;

    case InRowNumberInBlock:
      break;
    case InColNumberInBlock:
      break;

    case TwoRowOneNumberInTwoCol:
      break;
    case TwoColOneNumberInTwoRow:
      break;
    default:
      break;
  }
}

void usage(const char* exec) {
  fprintf(stderr, "Usage: %s <file>\n", exec);
  fprintf(stderr, "\t<file>: The sudoku file path\n");
  fprintf(stderr, "\tor using %s with stdin\n", exec);
}

int main(int argc, char* argv[]) {
  if (argc != 1 && argc != 2) {
    usage(argv[0]);
    return -1;
  }

  FILE* file = stdin;
  if (argc == 2) {
    file = NULL;
    file = open_file_for_read(argv[1]);
    if (file == NULL) {
      usage(argv[0]);
      return -1;
    }
  }
  int board[BOARD_SIZE];
  if (get_sudoku_from_file(board, BOARD_SIZE, file) == false) {
    fprintf(stderr, "Read sudoku from %s failed\n", argv[1]);
    usage(argv[0]);
    fclose(file);
    return -1;
  }
  int board_dancing[BOARD_SIZE];
  for (int i = 0; i < BOARD_SIZE; i++) {
    board_dancing[i] = board[i];
  }

  {
    Sudoku* sudo = CreateSudoku(read_board, write_board, solve_process, (void*)board);
    int cnt = GetKnownCount(sudo);
    printf("Sudoku Known Count: %d\n", cnt);
    printf("Calculate step by step\n");
    int num = CalculateSudokuAll(sudo, false, NULL, NULL);
    printf("Answer Count: %d\n", num);
    display_sudoku(board);
    int status = VerifySudokuBoard(board);
    printf("Verify: %s\n", status ? "True" : "False");
    DestroySudoku(sudo);
  }
  //  printf("\n");
  //  {
  //    Sudoku* sudo = CreateSudoku(read_board, write_board_dancing, NULL, (void*)board_dancing);
  //    printf("Calculate using dancing\n");
  //    int num = CalculateSudokuAll(sudo, true, NULL, NULL);
  //    printf("Answer Count: %d\n", num);
  //    printf("One of it:\n");
  //    display_sudoku(board_dancing);
  //    int status = VerifySudokuBoard(board_dancing);
  //    printf("Verify: %s\n", status ? "True" : "False");
  //    DestroySudoku(sudo);
  //  }

  return 0;
}
