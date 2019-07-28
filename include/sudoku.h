#ifndef sudoku_h
#define sudoku_h

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

typedef struct sudoku sudoku;

typedef int (*sudokuReadData)(int row, int col);
typedef void (*sudokuWriteData)(int row, int col, int value);

SUDOKU_API sudoku* CreateSudoku(sudokuReadData readFunc, sudokuWriteData writeFunc);
SUDOKU_API void SudokuReload(sudoku* sudo, sudokuReadData readFunc, sudokuWriteData writeFunc);
SUDOKU_API bool SudokuVerification(sudoku* sudo);
SUDOKU_API void SudokuCalculateOne(sudoku* sudo);
SUDOKU_API void SudokuCalculateAll(sudoku* sudo);

#endif
