#include <stdlib.h>

#include <bool-matrix.h>
#include <sudoku.h>

#include "SudokuLib.h"

/*
 * Class:     SudokuLib
 * Method:    CreateBoolMatrix
 * Signature: (III)J
 */
JNIEXPORT jlong JNICALL Java_SudokuLib_CreateBoolMatrix(JNIEnv* env, jclass cls, jint row, jint col, jint maxNodes) {
  return (jlong)CreateBoolMatrix(row, col, maxNodes);
}

/*
 * Class:     SudokuLib
 * Method:    DestroyBoolMatrix
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_SudokuLib_DestroyBoolMatrix(JNIEnv* env, jclass cls, jlong matrix) {
  DestroyBoolMatrix((BoolMatrix*)matrix);
}

/*
 * Class:     SudokuLib
 * Method:    SetMatrixRowData
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL Java_SudokuLib_SetMatrixRowData(JNIEnv* env, jclass cls, jlong matrix, jintArray array) {
  jsize size = (*env)->GetArrayLength(env, array);
  jint* row = alloca(sizeof(jint) * size);
  (*env)->GetIntArrayRegion(env, array, 0, size, row);
  SetMatrixRowData((BoolMatrix*)matrix, (const int*)row, (int)size);
}

typedef struct JavaData {
  JNIEnv* env;
  jobject obj;
  void* data;
} JavaData;
static void Default_AnswerCallback(void* data, const int* answer, int size) {
  JavaData* tmp = (JavaData*)data;
  JNIEnv* env = tmp->env;
  jobject obj = tmp->obj;

  jintArray array = (*env)->NewIntArray(env, size);
  (*env)->SetIntArrayRegion(env, array, 0, size, answer);

  jclass cls = (*env)->GetObjectClass(env, obj);
  jmethodID callback = (*env)->GetMethodID(env, cls, "AnswerCallback", "([I)V");
  (*env)->CallVoidMethod(env, obj, callback, array);
}
/*
 * Class:     SudokuLib
 * Method:    DancingLinks
 * Signature: (JIJJ)I
 */
JNIEXPORT jint JNICALL Java_SudokuLib_DancingLinks(JNIEnv* env, jclass cls, jlong matrix, jint just, jobject obj) {
  bool justOne = just != 0;
  JavaData data;
  data.env = env;
  data.obj = obj;
  return (jint)DancingLinks((BoolMatrix*)matrix, justOne, Default_AnswerCallback, (void*)&data);
}

// row and col are in the range of 1-9
static int Default_SudokuReadData(void* data, int row, int col) {
  JavaData* tmp = (JavaData*)data;
  JNIEnv* env = tmp->env;
  jobject obj = tmp->obj;

  jclass cls = (*env)->GetObjectClass(env, obj);
  jmethodID callback = (*env)->GetMethodID(env, cls, "SudokuReadData", "(II)I");
  return (int)(*env)->CallIntMethod(env, obj, callback, row, col);
}
// row col and value are in the range of 1-9
static void Default_SudokuWriteData(void* data, int row, int col, int value, SolveType type) {
  JavaData* tmp = (JavaData*)data;
  JNIEnv* env = tmp->env;
  jobject obj = tmp->obj;

  jclass cls = (*env)->GetObjectClass(env, obj);
  jmethodID callback = (*env)->GetMethodID(env, cls, "SudokuWriteData", "(IIII)V");
  (*env)->CallVoidMethod(env, obj, callback, row, col, value, (int)type);
}
static void Default_SolveProcessCallback(void* data, SolveProcedure* proc) {
  JavaData* tmp = (JavaData*)data;
  JNIEnv* env = tmp->env;
  jobject obj = tmp->obj;

  jclass classSolve = (*env)->FindClass(env, "SolveProcedure");
  jmethodID constructor = (*env)->GetMethodID(env, classSolve, "<init>", "()V");
  jobject now = (*env)->NewObject(env, classSolve, constructor);
  jfieldID field = (*env)->GetFieldID(env, classSolve, "type", "I");
  (*env)->SetIntField(env, now, field, (int)proc->type);

  jclass cls = (*env)->GetObjectClass(env, obj);
  jmethodID callback = (*env)->GetMethodID(env, cls, "SolveProcessCallback", "(LSolveProcedure)V");
  (*env)->CallIntMethod(env, obj, callback, now);
}

/*
 * Class:     SudokuLib
 * Method:    CreateSudoku
 * Signature: (LISudokuCallback;)J
 */
JNIEXPORT jlong JNICALL Java_SudokuLib_CreateSudoku(JNIEnv* env, jclass cls, jobject obj) {
  JavaData* pData = (JavaData*)malloc(sizeof(JavaData));
  pData->env = env;
  pData->obj = obj;
  pData->data =
      (void*)CreateSudoku(Default_SudokuReadData, Default_SudokuWriteData, Default_SolveProcessCallback, (void*)pData);
  return (jlong)pData;
}

/*
 * Class:     SudokuLib
 * Method:    DestroySudoku
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_SudokuLib_DestroySudoku(JNIEnv* env, jclass cls, jlong jData) {
  JavaData* pData = (JavaData*)jData;
  DestroySudoku((Sudoku*)pData->data);
  free(pData);
}

/*
 * Class:     SudokuLib
 * Method:    VerifySudokuBoard
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_SudokuLib_VerifySudokuBoard(JNIEnv* env, jclass cls, jintArray array) {
  jsize size = (*env)->GetArrayLength(env, array);
  jint* board = alloca(sizeof(jint) * size);
  (*env)->GetIntArrayRegion(env, array, 0, size, board);
  return (jint)VerifySudokuBoard((const int*)board);
}

/*
 * Class:     SudokuLib
 * Method:    VerifySudoku
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_SudokuLib_VerifySudoku(JNIEnv* env, jclass cls, jlong jData) {
  JavaData* pData = (JavaData*)jData;
  Sudoku* sudo = (Sudoku*)pData->data;
  return (jint)VerifySudoku(sudo);
}

/*
 * Class:     SudokuLib
 * Method:    GetKnownCount
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_SudokuLib_GetKnownCount(JNIEnv* env, jclass cls, jlong jData) {
  JavaData* pData = (JavaData*)jData;
  Sudoku* sudo = (Sudoku*)pData->data;
  return (jint)GetKnownCount(sudo);
}

/*
 * Class:     SudokuLib
 * Method:    MakeResultString
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_SudokuLib_MakeResultString(JNIEnv* env, jclass cls, jlong jData) {
  JavaData* pData = (JavaData*)jData;
  Sudoku* sudo = (Sudoku*)pData->data;
  char buffer[RESULT_BUFFER_SIZE];
  MakeResultString(sudo, buffer, RESULT_BUFFER_SIZE);
  return (*env)->NewStringUTF(env, buffer);
}

// ans is a null terminate char array
static void Default_SudokuAnswerCallback(void* data, const char* ans) {
}

/*
 * Class:     SudokuLib
 * Method:    CalculateSudokuAll
 * Signature: (JILISudokuAnswerCallback;)I
 */
JNIEXPORT jint JNICALL
Java_SudokuLib_CalculateSudokuAll(JNIEnv* env, jclass cls, jlong jData, jint justOne, jobject obj) {
  JavaData* pData = (JavaData*)jData;
  Sudoku* sudo = (Sudoku*)pData->data;
  JavaData tmpData;
  tmpData.env = env;
  tmpData.data = (void*)sudo;
  tmpData.obj = obj;
  return (jint)CalculateSudokuAll(sudo, justOne != 0, Default_SudokuAnswerCallback, &tmpData);
}

/*
 * Class:     SudokuLib
 * Method:    SolveTypeName
 * Signature: (LSolveType;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_SudokuLib_SolveTypeName(JNIEnv* env, jclass cls, jint type) {
  return (*env)->NewStringUTF(env, SolveTypeName((SolveType)type));
}

/*
 * Class:     SudokuLib
 * Method:    ImproveTypeName
 * Signature: (LImproveType;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_SudokuLib_ImproveTypeName(JNIEnv* env, jclass cls, jint type) {
  return (*env)->NewStringUTF(env, ImproveTypeName((ImproveType)type));
}
