#ifndef sudoku_h
#define sudoku_h

#include <stddef.h>
#include <stdbool.h>

#if defined(SUDOKU_BUILD_AS_DLL)
#if defined(SUDOKU_CORE)
#define SUDOKU_API __declspec(dllexport)
#else
#define SUDOKU_API __declspec(dllimport)
#endif
#else
#define SUDOKU_API extern
#endif

// 9*9*2:num+' ', 9*2:every line has ' '*2, 9:every line has '\n', 2*'\n'+'\0'
#define RESULT_BUFFER_SIZE (9 * 9 * 2 + 9 * 2 + 9 + 2 + 1)

typedef struct Sudoku Sudoku;
typedef enum SolveType { None = 0 } SolveType;

// row and col are in the range of 1-9
typedef int (*SudokuReadData)(int row, int col);
// row and col are in the range of 1-9
typedef void (*SudokuWriteData)(int row, int col, int value, SolveType type);
// ans is a null terminate char array
typedef void (*SudokuAnswerCallback)(void* data, const char* ans);

SUDOKU_API Sudoku* CreateSudoku(SudokuReadData readFunc, SudokuWriteData writeFunc);
SUDOKU_API void DestroySudoku(Sudoku* sudo);
SUDOKU_API bool VerifySudokuBoard(int* board);
SUDOKU_API bool VerifySudoku(Sudoku* sudo);
SUDOKU_API int GetKnownCount(Sudoku* sudo);
// buffer must has size of RESULT_BUFFER_SIZE
SUDOKU_API void MakeResultString(Sudoku* sudo, char* buffer, int size);
SUDOKU_API int CalculateSudokuAll(Sudoku* sudo, bool dancing, SudokuAnswerCallback cb, void* data);

typedef struct BoolMatrix BoolMatrix;

// answer is an array with row number in [0, rows-1]
typedef void (*AnswerCallback)(void* data, const int* answer, int size);

// rows is the number of matrix row
// cols is the number of matrix column
// maxNodes is the number of 1 in the matrix
SUDOKU_API BoolMatrix* CreateBoolMatrix(int rows, int cols, int maxNodes);
SUDOKU_API void DestroyBoolMatrix(BoolMatrix* matrix);
// data is an array with one position in that row, position are in the range of [0, cols-1]
SUDOKU_API void SetMatrixRowData(BoolMatrix* matrix, const int* data, int size);
// return the number of this call has calculated(the result)
SUDOKU_API int DancingLinks(BoolMatrix* matrix, bool justOne, AnswerCallback cb, void* data);

#endif
