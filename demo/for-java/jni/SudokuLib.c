// #include <stdio.h>
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
 * Signature: (J[I)V
 */
JNIEXPORT void JNICALL Java_SudokuLib_SetMatrixRowData(JNIEnv* env, jclass cls, jlong matrix, jintArray array) {
  jsize size = (*env)->GetArrayLength(env, array);
#ifdef _WIN32
  jint* row = (jint*)malloc(sizeof(jint) * size);
#else
  jint* row = (jint*)alloca(sizeof(jint) * size);
#endif
  (*env)->GetIntArrayRegion(env, array, 0, size, row);
  SetMatrixRowData((BoolMatrix*)matrix, (const int*)row, (int)size);
#ifdef _WIN32
  free(row);
#endif
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
 * Signature: (JZLIMatrixCallback;)I
 */
JNIEXPORT jint JNICALL Java_SudokuLib_DancingLinks(JNIEnv* env, jclass cls, jlong matrix, jboolean just, jobject obj) {
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
  field = (*env)->GetFieldID(env, classSolve, "gridOneX", "I");
  (*env)->SetIntField(env, now, field, (int)proc->gridOneX);
  field = (*env)->GetFieldID(env, classSolve, "gridOneY", "I");
  (*env)->SetIntField(env, now, field, (int)proc->gridOneY);
  field = (*env)->GetFieldID(env, classSolve, "gridTwoX", "I");
  (*env)->SetIntField(env, now, field, (int)proc->gridTwoX);
  field = (*env)->GetFieldID(env, classSolve, "gridTwoY", "I");
  (*env)->SetIntField(env, now, field, (int)proc->gridTwoY);
  field = (*env)->GetFieldID(env, classSolve, "gridThreeX", "I");
  (*env)->SetIntField(env, now, field, (int)proc->gridThreeX);
  field = (*env)->GetFieldID(env, classSolve, "gridThreeY", "I");
  (*env)->SetIntField(env, now, field, (int)proc->gridThreeY);
  field = (*env)->GetFieldID(env, classSolve, "numberOne", "I");
  (*env)->SetIntField(env, now, field, (int)proc->numberOne);
  field = (*env)->GetFieldID(env, classSolve, "numberTwo", "I");
  (*env)->SetIntField(env, now, field, (int)proc->numberTwo);
  field = (*env)->GetFieldID(env, classSolve, "numberThree", "I");
  (*env)->SetIntField(env, now, field, (int)proc->numberThree);
  field = (*env)->GetFieldID(env, classSolve, "panelRow", "I");
  (*env)->SetIntField(env, now, field, (int)proc->panelRow);
  field = (*env)->GetFieldID(env, classSolve, "panelCol", "I");
  (*env)->SetIntField(env, now, field, (int)proc->panelCol);
  field = (*env)->GetFieldID(env, classSolve, "number", "I");
  (*env)->SetIntField(env, now, field, (int)proc->number);
  field = (*env)->GetFieldID(env, classSolve, "line", "I");
  (*env)->SetIntField(env, now, field, (int)proc->line);
  field = (*env)->GetFieldID(env, classSolve, "rowOne", "I");
  (*env)->SetIntField(env, now, field, (int)proc->rowOne);
  field = (*env)->GetFieldID(env, classSolve, "rowTwo", "I");
  (*env)->SetIntField(env, now, field, (int)proc->rowTwo);
  field = (*env)->GetFieldID(env, classSolve, "rowThree", "I");
  (*env)->SetIntField(env, now, field, (int)proc->rowThree);
  field = (*env)->GetFieldID(env, classSolve, "colOne", "I");
  (*env)->SetIntField(env, now, field, (int)proc->colOne);
  field = (*env)->GetFieldID(env, classSolve, "colTwo", "I");
  (*env)->SetIntField(env, now, field, (int)proc->colTwo);
  field = (*env)->GetFieldID(env, classSolve, "colThree", "I");
  (*env)->SetIntField(env, now, field, (int)proc->colThree);

  jclass cls = (*env)->GetObjectClass(env, obj);
  jmethodID callback = (*env)->GetMethodID(env, cls, "SolveProcessCallback", "(LSolveProcedure;)V");
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
 * Method:    VerifySudoku
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_SudokuLib_VerifySudoku(JNIEnv* env, jclass cls, jlong jData) {
  JavaData* pData = (JavaData*)jData;
  Sudoku* sudo = (Sudoku*)pData->data;
  return (jboolean)VerifySudoku(sudo);
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
 * Signature: (JZLISudokuCallback;)I
 */
JNIEXPORT jint JNICALL
Java_SudokuLib_CalculateSudokuAll(JNIEnv* env, jclass cls, jlong jData, jboolean justOne, jobject obj) {
  JavaData* pData = (JavaData*)jData;
  // printf("%x %x\n", pData->env, pData->obj);
  // printf("%x %x\n", env, obj);
  pData->env = env;
  pData->obj = obj; // In java, obj only available in current call, so here must to update it
  Sudoku* sudo = (Sudoku*)pData->data;
  JavaData tmpData;
  tmpData.env = env;
  tmpData.data = (void*)sudo;
  tmpData.obj = obj;
  return (jint)CalculateSudokuAll(sudo, justOne != 0, Default_SudokuAnswerCallback, &tmpData);
}

/*
 * Class:     SudokuLib
 * Method:    VerifySudokuBoard
 * Signature: ([I)Z
 */
JNIEXPORT jboolean JNICALL Java_SudokuLib_VerifySudokuBoard(JNIEnv* env, jclass cls, jintArray array) {
  jsize size = (*env)->GetArrayLength(env, array);
#ifdef _WIN32
  jint* board = (jint*)malloc(sizeof(jint) * size);
#else
  jint* board = (jint*)alloca(sizeof(jint) * size);
#endif
  (*env)->GetIntArrayRegion(env, array, 0, size, board);
  jboolean ret = (jboolean)VerifySudokuBoard((const int*)board);
#ifdef _WIN32
  free(board);
#endif
  return ret;
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
