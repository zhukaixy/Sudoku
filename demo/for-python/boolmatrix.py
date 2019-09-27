import ctypes
import libsudoku


class BoolMatrix:
    """
    Bool Matrix
    """

    def __init__(self, rows, cols, maxNodes):
        self.handler = libsudoku.CreateBoolMatrix(rows, cols, maxNodes)

    def __del__(self):
        print("Destroy Bool Matrix")
        libsudoku.DestroyBoolMatrix(self.handler)

    def SetMatrixRowData(self, row):
        def ListToCArray(row):
            arrayType = ctypes.c_int * len(row)
            crow = arrayType(*row)
            return crow
        return libsudoku.SetMatrixRowData(self.handler, ListToCArray(row), len(row))

    def DancingLinks(self, onlyOne, callback):
        # typedef void (*AnswerCallback)(void* data, const int* answer, int size);
        AnswerCallback = ctypes.CFUNCTYPE(None,
                                          ctypes.c_void_p, ctypes.POINTER(ctypes.c_int), ctypes.c_int)

        def MatrixAnswerCallback(data, answer, size):
            answerList = ctypes.cast(
                answer, ctypes.POINTER(ctypes.c_int))
            ans = []
            for i in range(size):
                ans.append(answerList[i])
            callback(ans)
        return libsudoku.DancingLinks(self.handler, onlyOne, AnswerCallback(
            MatrixAnswerCallback), self.handler)
