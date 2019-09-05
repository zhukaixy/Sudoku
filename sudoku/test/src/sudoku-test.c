#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <CuTest.h>
#include <sudoku.h>
#include <sudodef.h>

// clang-format off
static int const puzzleOne[] = {
  0, 0, 0,  0, 1, 2,  3, 0, 0,
  1, 2, 3,  0, 8, 0,  4, 0, 0,
  8, 0, 4,  0, 7, 6,  5, 0, 0,

  7, 6, 5,  0, 0, 0,  0, 0, 0,
  0, 0, 0,  0, 0, 0,  0, 0, 0,
  0, 0, 0,  0, 0, 0,  7, 8, 9,

  0, 0, 7,  8, 9, 0,  1, 0, 3,
  0, 0, 1,  0, 3, 0,  9, 2, 5,
  0, 0, 9,  2, 5, 0,  0, 0, 0
};
static int const puzzleOneAnswer[] = {
  5, 7, 6,  4, 1, 2,  3, 9, 8,
  1, 2, 3,  5, 8, 9,  4, 7, 6,
  8, 9, 4,  3, 7, 6,  5, 1, 2,

  7, 6, 5,  9, 4, 8,  2, 3, 1,
  9, 1, 8,  7, 2, 3,  6, 5, 4,
  3, 4, 2,  1, 6, 5,  7, 8, 9,

  2, 5, 7,  8, 9, 4,  1, 6, 3,
  4, 8, 1,  6, 3, 7,  9, 2, 5,
  6, 3, 9,  2, 5, 1,  8, 4, 7
};
static char const puzzleOneAnswerStr[RESULT_BUFFER_SIZE] =
  "5 7 6  4 1 2  3 9 8 \n"
  "1 2 3  5 8 9  4 7 6 \n"
  "8 9 4  3 7 6  5 1 2 \n\n"
  "7 6 5  9 4 8  2 3 1 \n"
  "9 1 8  7 2 3  6 5 4 \n"
  "3 4 2  1 6 5  7 8 9 \n\n"
  "2 5 7  8 9 4  1 6 3 \n"
  "4 8 1  6 3 7  9 2 5 \n"
  "6 3 9  2 5 1  8 4 7 \n";
// clang-format on

typedef struct TestSudoku {
  // CuTest* tc;
  int board[81];
  SolveType types[81];
} TestSudoku;

static int read_data_func(void* data, int row, int col) { // row 1-9, col 1-9
  TestSudoku* testSudo = (TestSudoku*)data;
  int index = (row - 1) * 9 + col - 1;
  return testSudo->board[index];
}
static void write_data_func(void* data, int row, int col, int value, SolveType type) {
  TestSudoku* testSudo = (TestSudoku*)data;
  int index = (row - 1) * 9 + col - 1;
  testSudo->board[index] = value;
  testSudo->types[index] = type;
}

static void TestCreateSudoku(CuTest* tc) {
  TestSudoku testSudo;
  memset(&testSudo, 0, sizeof(TestSudoku));
  for (int i = 0; i < 81; i++) {
    testSudo.board[i] = puzzleOne[i];
  }
  Sudoku* sudo = NULL;
  sudo = CreateSudoku(NULL, write_data_func, NULL);
  CuAssertPtrEquals(tc, NULL, sudo);
  sudo = CreateSudoku(read_data_func, NULL, NULL);
  CuAssertPtrEquals(tc, NULL, sudo);

  sudo = CreateSudoku(read_data_func, write_data_func, (void*)&testSudo);
  CuAssertPtrNotNull(tc, sudo);
  CuAssertPtrEquals(tc, read_data_func, sudo->readData);
  CuAssertPtrEquals(tc, write_data_func, sudo->writeData);
  CuAssertPtrEquals(tc, (void*)&testSudo, sudo->dataIO);
  CuAssertTrue(tc, !sudo->hasWriteData);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      CuAssertIntEquals(tc, puzzleOne[i * 9 + j], sudo->sudoData[i][j][0]);
    }
  }
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      for (int k = 1; k < 10; k++) {
        CuAssertIntEquals(tc, k, sudo->sudoData[i][j][k]);
      }
    }
  }
  DestroySudoku(sudo);
  DestroySudoku(NULL);
}

void TestVerifySudoku(CuTest* tc) {
  TestSudoku testSudo;
  memset(&testSudo, 0, sizeof(TestSudoku));
  for (int i = 0; i < 81; i++) {
    testSudo.board[i] = puzzleOne[i];
  }

  Sudoku* sudo = CreateSudoku(read_data_func, write_data_func, &testSudo);
  bool result = VerifySudoku(sudo);
  CuAssertTrue(tc, !result);
  int count = GetKnownCount(sudo);
  CuAssertIntEquals(tc, 32, count);
  DestroySudoku(sudo);

  for (int i = 0; i < 81; i++) {
    testSudo.board[i] = puzzleOneAnswer[i];
  }
  sudo = CreateSudoku(read_data_func, write_data_func, &testSudo);
  result = VerifySudoku(sudo);
  CuAssertTrue(tc, result);
  count = GetKnownCount(sudo);
  CuAssertIntEquals(tc, 81, count);
  DestroySudoku(sudo);

  CuAssertTrue(tc, !VerifySudokuBoard(puzzleOne));
  CuAssertTrue(tc, VerifySudokuBoard(puzzleOneAnswer));
}

void sudoku_answer_cb(void* data, const char* str) {
  char* ansSudo = (char*)data;
  for (int i = 0; i < RESULT_BUFFER_SIZE; i++) {
    ansSudo[i] = str[i];
  }
}
void TestCalculateSudokuAll(CuTest* tc) {
  TestSudoku testSudo;
  memset(&testSudo, 0, sizeof(TestSudoku));
  for (int i = 0; i < 81; i++) {
    testSudo.board[i] = puzzleOne[i];
  }
  char ansSudo[RESULT_BUFFER_SIZE];
  memset(ansSudo, 0, sizeof(char) * RESULT_BUFFER_SIZE);

  // dancing links
  Sudoku* sudo = CreateSudoku(read_data_func, write_data_func, (void*)&testSudo);
  int num = CalculateSudokuAll(sudo, true, sudoku_answer_cb, (void*)ansSudo);
  CuAssertTrue(tc, VerifySudoku(sudo));
  CuAssertIntEquals(tc, 1, num);
  CuAssertStrEquals(tc, puzzleOneAnswerStr, ansSudo);
  DestroySudoku(sudo);
  for (int i = 0; i < 81; i++) {
    CuAssertTrue(tc, testSudo.types[i] == None);
  }
  CuAssertTrue(tc, VerifySudokuBoard(testSudo.board));
  sudo = CreateSudoku(read_data_func, write_data_func, (void*)&testSudo);
  bool result = VerifySudoku(sudo);
  CuAssertTrue(tc, result);
  int count = GetKnownCount(sudo);
  CuAssertIntEquals(tc, 81, count);
  DestroySudoku(sudo);

  memset(&testSudo, 0, sizeof(TestSudoku));
  for (int i = 0; i < 81; i++) {
    testSudo.board[i] = puzzleOne[i];
  }
  memset(ansSudo, 0, sizeof(char) * RESULT_BUFFER_SIZE);

  // step by step
  sudo = CreateSudoku(read_data_func, write_data_func, (void*)&testSudo);
  num = CalculateSudokuAll(sudo, false, sudoku_answer_cb, (void*)ansSudo);
  CuAssertTrue(tc, VerifySudoku(sudo));
  CuAssertIntEquals(tc, 1, num);
  CuAssertStrEquals(tc, puzzleOneAnswerStr, ansSudo);
  DestroySudoku(sudo);
  sudo = CreateSudoku(read_data_func, write_data_func, (void*)&testSudo);
  result = VerifySudoku(sudo);
  CuAssertTrue(tc, result);
  count = GetKnownCount(sudo);
  CuAssertIntEquals(tc, 81, count);
  DestroySudoku(sudo);
}

typedef struct TestMatrix {
  int answer[6];
  int callCount;
} TestMatrix;

static int const rightAnswer[6] = {3, 0, 4, 0, 0, 0};

// every int in answer array must in the range of [0, 6-1]
void matrix_answer_cb(void* data, const int* answer, int size) {
  TestMatrix* testMat = (TestMatrix*)data;
  testMat->callCount++;
  memset(testMat->answer, 0, sizeof(int) * 6);
  for (int i = 0; i < size; i++) {
    testMat->answer[i] = answer[i];
  }
}
void TestBoolMatrix(CuTest* tc) {
  TestMatrix testMat;
  memset(&testMat, 0, sizeof(TestMatrix));

  int tmp1[] = {2, 4, 5};
  int tmp2[] = {0, 3, 6};
  int tmp3[] = {1, 2, 5};
  int tmp4[] = {0, 3};
  int tmp5[] = {1, 6};
  int tmp6[] = {3, 4, 6};
  BoolMatrix* matrix = CreateBoolMatrix(6, 7, 16);
  SetMatrixRowData(matrix, tmp1, 3);
  SetMatrixRowData(matrix, tmp2, 3);
  SetMatrixRowData(matrix, tmp3, 3);
  SetMatrixRowData(matrix, tmp4, 2);
  SetMatrixRowData(matrix, tmp5, 2);
  SetMatrixRowData(matrix, tmp6, 3);
  int num = DancingLinks(matrix, false, matrix_answer_cb, &testMat);
  DestroyBoolMatrix(matrix);

  CuAssertIntEquals(tc, 1, testMat.callCount);
  CuAssertIntEquals(tc, 1, num);
  for (int i = 0; i < 6; i++) {
    CuAssertIntEquals(tc, rightAnswer[i], testMat.answer[i]);
  }
}

CuSuite* SudokuGetSuite() {
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, TestCreateSudoku);
  SUITE_ADD_TEST(suite, TestVerifySudoku);
  SUITE_ADD_TEST(suite, TestCalculateSudokuAll);
  SUITE_ADD_TEST(suite, TestBoolMatrix);

  return suite;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  CuSuite* suite = CuSuiteNew();

  CuSuiteAddSuite(suite, SudokuGetSuite());

  CuSuiteRun(suite);
  CuString* output = CuStringNew();
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);

  return 0;
}
