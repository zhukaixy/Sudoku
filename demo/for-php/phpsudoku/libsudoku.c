#include <stdlib.h>
#include "php.h"
#include "sudoku/bool-matrix.h"
#include "sudoku/sudoku.h"

// BoolMatrix
PHP_FUNCTION(PHPCreateBoolMatrix)
{
    long rows, cols, maxNodes;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &rows, &cols, &maxNodes) == FAILURE)
    {
        return;
    }
    // php_printf("Hello PHPCreateBoolMatrix!\n");
    BoolMatrix* matrix = CreateBoolMatrix((int)rows, (int)cols, (int)maxNodes);
    RETVAL_LONG((long)matrix);
}

PHP_FUNCTION(PHPDestroyBoolMatrix)
{
    long matrix;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &matrix) == FAILURE)
    {
        return;
    }
    DestroyBoolMatrix((BoolMatrix*)matrix);
}

PHP_FUNCTION(PHPSetMatrixRowData)
{
    long matrix;
    zval* data;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "la", &matrix, &data) == FAILURE)
    {
        return;
    }
    int size = zend_hash_num_elements(Z_ARRVAL_P(data));
    int* arr = (int*)alloca(sizeof(int) * size);
    // php_printf("PHPSetMatrixRowData size: %d, value: ", size);
    for (int i = 0; i < size; i++)
    {
        zval* value = zend_hash_index_find(Z_ARRVAL_P(data), i);
        // php_printf("%d ", (int)Z_LVAL(*value));
        arr[i] = (int)Z_LVAL(*value);
    }
    // php_printf("\n");
    SetMatrixRowData((BoolMatrix*)matrix, arr, size);
}

static void answer_callback(void* data, const int* answer, int size)
{
    // zval* cb = (zval*)data;
    const char* name = "MatrixAnswerCallback";
    zend_string* funcName = zend_string_init(name, strlen(name), 0);
    zval funcNameForCall, retForCall, paramsForCall[1];
    ZVAL_STR(&funcNameForCall, funcName);
    zval *ans, zans;
    ans = &zans;
    // array_init(ans);
    array_init_size(ans, size);
    for (int i = 0; i < size; i++)
    {
        add_index_long(ans, i, answer[i]+1);
    }
    paramsForCall[0] = zans;
    call_user_function(EG(function_table), NULL, &funcNameForCall, &retForCall, 1, paramsForCall);
    zend_string_release(funcName);
}

PHP_FUNCTION(PHPDancingLinks)
{
    long matrix;
    zend_bool justOne;
    // zval* cb;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lb", &matrix, &justOne) == FAILURE)
    {
        return;
    }
    int count = DancingLinks((BoolMatrix*)matrix, (bool)justOne, answer_callback, NULL);
    RETVAL_LONG((long)count);
}


// Sudoku
static int sudoku_read_data(void* data, int row, int col)
{
    const char* name = "SudokuReadData";
    zend_string* funcName = zend_string_init(name, strlen(name), 0);
    zval funcNameForCall, retForCall, paramsForCall[2];
    ZVAL_STR(&funcNameForCall, funcName);
    ZVAL_LONG(&paramsForCall[0], row);
    ZVAL_LONG(&paramsForCall[1], col);
    call_user_function(EG(function_table), NULL, &funcNameForCall, &retForCall, 2, paramsForCall);
    zend_string_release(funcName);
    return (int)Z_LVAL(retForCall);
}
static void sudoku_write_data(void* data, int row, int col, int value, SolveType type)
{
    const char* name = "SudokuWriteData";
    zend_string* funcName = zend_string_init(name, strlen(name), 0);
    zval funcNameForCall, retForCall, paramsForCall[4];
    ZVAL_STR(&funcNameForCall, funcName);
    ZVAL_LONG(&paramsForCall[0], row);
    ZVAL_LONG(&paramsForCall[1], col);
    ZVAL_LONG(&paramsForCall[2], value);
    ZVAL_LONG(&paramsForCall[3], (int)type);
    call_user_function(EG(function_table), NULL, &funcNameForCall, &retForCall, 4, paramsForCall);
    zend_string_release(funcName);
}
static void sudoku_solve_process(void* data, SolveProcedure* proc)
{
    const char* name = "SudokuProcCallback";
    zend_string* funcName = zend_string_init(name, strlen(name), 0);
    zval funcNameForCall, retForCall, paramsForCall[1];
    ZVAL_STR(&funcNameForCall, funcName);

    zval *pzProc, zProc;
    pzProc = &zProc;
    // array_init(pzProc);
    array_init_size(pzProc, 20);
    add_assoc_long(pzProc, "type", (long)proc->type);
    add_assoc_long(pzProc, "gridOneX", (long)proc->gridOneX);
    add_assoc_long(pzProc, "gridOneY", (long)proc->gridOneY);
    add_assoc_long(pzProc, "gridTwoX", (long)proc->gridTwoX);
    add_assoc_long(pzProc, "gridTwoY", (long)proc->gridTwoY);
    add_assoc_long(pzProc, "gridThreeX", (long)proc->gridThreeX);
    add_assoc_long(pzProc, "gridThreeY", (long)proc->gridThreeY);
    add_assoc_long(pzProc, "numberOne", (long)proc->numberOne);
    add_assoc_long(pzProc, "numberTwo", (long)proc->numberTwo);
    add_assoc_long(pzProc, "numberThree", (long)proc->numberThree);
    add_assoc_long(pzProc, "panelRow", (long)proc->panelRow);
    add_assoc_long(pzProc, "panelCol", (long)proc->panelCol);
    add_assoc_long(pzProc, "number", (long)proc->number);
    add_assoc_long(pzProc, "line", (long)proc->line);
    add_assoc_long(pzProc, "rowOne", (long)proc->rowOne);
    add_assoc_long(pzProc, "rowTwo", (long)proc->rowTwo);
    add_assoc_long(pzProc, "rowThree", (long)proc->rowThree);
    add_assoc_long(pzProc, "colOne", (long)proc->colOne);
    add_assoc_long(pzProc, "colTwo", (long)proc->colTwo);
    add_assoc_long(pzProc, "colThree", (long)proc->colThree);

    paramsForCall[0] = zProc;
    call_user_function(EG(function_table), NULL, &funcNameForCall, &retForCall, 1, paramsForCall);
    zend_string_release(funcName);
}
static void sudoku_answer_callback(void* data, const char* ans)
{
    const char* name = "SudokuAnswerCallback";
    zend_string* funcName = zend_string_init(name, strlen(name), 0);
    zval funcNameForCall, retForCall, paramsForCall[1];
    ZVAL_STR(&funcNameForCall, funcName);
    zend_string* answer = zend_string_init(ans, strlen(ans), 0);
    ZVAL_STR(&paramsForCall[0], answer);
    call_user_function(EG(function_table), NULL, &funcNameForCall, &retForCall, 1, paramsForCall);
    zend_string_release(funcName);
}

PHP_FUNCTION(PHPCreateSudoku)
{
    Sudoku* sudo = CreateSudoku(sudoku_read_data, sudoku_write_data, sudoku_solve_process, NULL);
    RETVAL_LONG((long)sudo);
}

PHP_FUNCTION(PHPDestroySudoku)
{
    long sudo;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &sudo) == FAILURE)
    {
        return;
    }
    DestroySudoku((Sudoku*)sudo);
}

PHP_FUNCTION(PHPVerifySudoku)
{
    long sudo;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &sudo) == FAILURE)
    {
        return;
    }
    bool status = VerifySudoku((Sudoku*)sudo);
    RETVAL_BOOL(status);
}

PHP_FUNCTION(PHPGetKnownCount)
{
    long sudo;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &sudo) == FAILURE)
    {
        return;
    }
    int count = GetKnownCount((Sudoku*)sudo);
    RETVAL_LONG(count);
}

PHP_FUNCTION(PHPMakeResultString)
{
    long sudo;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &sudo) == FAILURE)
    {
        return;
    }
    char buffer[RESULT_BUFFER_SIZE];
    MakeResultString((Sudoku*)sudo, buffer, RESULT_BUFFER_SIZE);
    zend_string* result = zend_string_init(buffer, strlen(buffer), 0);
    RETVAL_STR(result);
}

PHP_FUNCTION(PHPCalculateSudokuAll)
{
    long sudo;
    zend_bool dancing;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lb", &sudo, &dancing) == FAILURE)
    {
        return;
    }
    int cnt = CalculateSudokuAll((Sudoku*)sudo, (bool)dancing, sudoku_answer_callback, NULL);
    RETVAL_LONG(cnt);
}

PHP_FUNCTION(PHPVerifySudokuBoard)
{
    zval* data;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &data) == FAILURE)
    {
        return;
    }
    int size = zend_hash_num_elements(Z_ARRVAL_P(data));
    int* arr = (int*)alloca(sizeof(int) * size);
    // php_printf("PHPSetMatrixRowData size: %d, value: ", size);
    for (int i = 0; i < size; i++)
    {
        zval* value = zend_hash_index_find(Z_ARRVAL_P(data), i);
        // php_printf("%d ", (int)Z_LVAL(*value));
        arr[i] = (int)Z_LVAL(*value);
    }
    // php_printf("\n");
    bool status = VerifySudokuBoard(arr);
    RETVAL_BOOL(status);
}

PHP_FUNCTION(PHPSolveTypeName)
{
    long type;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &type) == FAILURE)
    {
        return;
    }
    const char* pName = SolveTypeName((SolveType)type);
    zend_string* name = zend_string_init(pName, strlen(pName), 0);
    RETVAL_STR(name);
}

PHP_FUNCTION(PHPImproveTypeName)
{
    long type;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &type) == FAILURE)
    {
        return;
    }
    const char* pName = ImproveTypeName((ImproveType)type);
    zend_string* name = zend_string_init(pName, strlen(pName), 0);
    RETVAL_STR(name);
}
