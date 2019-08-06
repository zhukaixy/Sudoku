#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <CuTest.h>
#include <sudoku.h>
#include <sudodef.h>

// clang-format off
static int data[] = {0, 0, 0,   0, 1, 2,   3, 0, 0,
                     1, 2, 3,   0, 8, 0,   4, 0, 0,
                     8, 0, 4,   0, 7, 6,   5, 0, 0,

                     7, 6, 5,   0, 0, 0,   0, 0, 0,
                     0, 0, 0,   0, 0, 0,   0, 0, 0,
                     0, 0, 0,   0, 0, 0,   7, 8, 9,

                     0, 0, 7,   8, 9, 0,   1, 0, 3,
                     0, 0, 1,   0, 3, 0,   9, 2, 5,
                     0, 0, 9,   2, 5, 0,   0, 0, 0};
// clang-format on
void* testRealloc(void* ptr, size_t size) {
  return realloc(ptr, size);
}
int testReadData(int row, int col) { // row 1-9, col 1-9
  return data[(row - 1) * 9 + col - 1];
}
void testWriteData(int row, int col, int value) {
  data[(row - 1) * 9 + col - 1] = value;
}

void TestSudokuCreate(CuTest* tc) {
  sudoku* sudo = NULL;
  sudo = SudokuCreate(NULL, testReadData, testWriteData);
  CuAssertPtrEquals(tc, NULL, sudo);
  sudo = SudokuCreate(testRealloc, NULL, testWriteData);
  CuAssertPtrEquals(tc, NULL, sudo);
  sudo = SudokuCreate(testRealloc, testReadData, NULL);
  CuAssertPtrEquals(tc, NULL, sudo);

  sudo = SudokuCreate(testRealloc, testReadData, testWriteData);
  CuAssertPtrNotNull(tc, sudo);
  CuAssertPtrEquals(tc, testRealloc, sudo->realloc);
  CuAssertPtrEquals(tc, testReadData, sudo->readData);
  CuAssertPtrEquals(tc, testWriteData, sudo->writeData);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      CuAssertIntEquals(tc, data[i * 9 + j], sudo->sudoData[i][j][0]);
    }
  }
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      for (int k = 1; k < 10; k++) {
        CuAssertIntEquals(tc, k, sudo->sudoData[i][j][k]);
      }
    }
  }
  SudokuDestroy(sudo);
  SudokuDestroy(NULL);
}

// clang-format off
static int data2[] = {0, 0, 0,   0, 1, 2,   3, 0, 0,
                      1, 2, 3,   0, 8, 0,   4, 0, 0,
                      8, 0, 4,   0, 7, 6,   5, 0, 0,

                      7, 6, 5,   0, 0, 0,   0, 0, 0,
                      0, 0, 0,   0, 0, 0,   0, 0, 0,
                      0, 0, 0,   0, 0, 0,   7, 8, 9,

                      0, 0, 7,   8, 9, 0,   1, 0, 3,
                      0, 0, 1,   0, 3, 0,   9, 2, 5,
                      0, 0, 9,   2, 5, 0,   0, 0, 0};
// clang-format on
int testReadData2(int row, int col) { // row 1-9, col 1-9
  return data2[(row - 1) * 9 + col - 1];
}
void testWriteData2(int row, int col, int value) {
  data2[(row - 1) * 9 + col - 1] = value;
}

void TestSudokuReload(CuTest* tc) {
  sudoku* sudo = SudokuCreate(testRealloc, testReadData, testWriteData);
  SudokuReload(NULL, NULL, NULL);
  SudokuReload(sudo, testReadData2, NULL);
  CuAssertPtrEquals(tc, testReadData2, sudo->readData);
  CuAssertPtrEquals(tc, testWriteData, sudo->writeData);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      CuAssertIntEquals(tc, data[i * 9 + j], sudo->sudoData[i][j][0]);
    }
  }
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      for (int k = 1; k < 10; k++) {
        CuAssertIntEquals(tc, k, sudo->sudoData[i][j][k]);
      }
    }
  }
  SudokuReload(sudo, NULL, testWriteData2);
  CuAssertPtrEquals(tc, testReadData2, sudo->readData);
  CuAssertPtrEquals(tc, testWriteData2, sudo->writeData);
  SudokuDestroy(sudo);
}

void TestSudokuVerify(CuTest* tc) {
  sudoku* sudo = SudokuCreate(testRealloc, testReadData, testWriteData);
  bool result = SudokuVerify(sudo);
  CuAssertTrue(tc, !result);
  SudokuDestroy(sudo);
}

void TestSudokuCalculateOne(CuTest* tc) {
}

void TestSudokuCalculateAll(CuTest* tc) {
}

CuSuite* SudokuGetSuite() {
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, TestSudokuCreate);
  SUITE_ADD_TEST(suite, TestSudokuReload);
  SUITE_ADD_TEST(suite, TestSudokuVerify);
  SUITE_ADD_TEST(suite, TestSudokuCalculateOne);
  SUITE_ADD_TEST(suite, TestSudokuCalculateAll);

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
