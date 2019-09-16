#include <stdlib.h>

#include <bool-matrix.h>
// #include <sudoku.h>

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
} JavaData;
static void default_answer_callback(void* data, const int* answer, int size) {
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
  return (jint)DancingLinks((BoolMatrix*)matrix, justOne, default_answer_callback, (void*)&data);
}
