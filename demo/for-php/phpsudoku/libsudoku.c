#include <stdlib.h>
#include "php.h"
#include "sudoku/bool-matrix.h"

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
