#ifndef _BOOL_MATRIX_H_
#define _BOOL_MATRIX_H_

#include <stdbool.h>

#if defined(SUDOKU_BUILD_AS_DLL)
#if defined(SUDOKU_CORE)
#define BOOL_MATRIX_API __declspec(dllexport) // for sudoku.dll
#else
#define BOOL_MATRIX_API __declspec(dllimport) // for user who use sudoku.dll, with SUDOKU_BUILD_AS_DLL
#endif
#else
#define BOOL_MATRIX_API extern
#endif

typedef struct BoolMatrix BoolMatrix;

// answer is an array with row number in [0, rows-1]
typedef void (*AnswerCallback)(void* data, const int* answer, int size);

// rows is the number of matrix row
// cols is the number of matrix column
// maxNodes is the number of 1 in the matrix
BOOL_MATRIX_API BoolMatrix* CreateBoolMatrix(int rows, int cols, int maxNodes);
BOOL_MATRIX_API void DestroyBoolMatrix(BoolMatrix* matrix);
// data is an array with one position in that row, position are in the range of [0, cols-1]
BOOL_MATRIX_API void SetMatrixRowData(BoolMatrix* matrix, const int* data, int size);
// return the number of this call has calculated(the result)
BOOL_MATRIX_API int DancingLinks(BoolMatrix* matrix, bool justOne, AnswerCallback cb, void* data);

#endif
