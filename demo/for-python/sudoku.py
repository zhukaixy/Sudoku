import ctypes
import libsudoku


class SolveProcedure(ctypes.Structure):
    _fields_ = [("type", ctypes.c_int),
                ("gridOneX", ctypes.c_int),  # [1, 9]
                ("gridOneY", ctypes.c_int),
                ("gridTwoX", ctypes.c_int),
                ("gridTwoY", ctypes.c_int),
                ("gridThreeX", ctypes.c_int),
                ("gridThreeY", ctypes.c_int),
                ("numberOne", ctypes.c_int),  # [1, 9]
                ("numberTwo", ctypes.c_int),
                ("numberThree", ctypes.c_int),
                ("panelRow", ctypes.c_int),  # [1, 3]
                ("panelCol", ctypes.c_int),
                ("number", ctypes.c_int),  # [1, 9]
                ("line", ctypes.c_int),  # [1, 9]
                ("rowOne", ctypes.c_int),  # [1, 9]
                ("rowTwo", ctypes.c_int),
                ("rowThree", ctypes.c_int),
                ("colOne", ctypes.c_int),
                ("colTwo", ctypes.c_int),
                ("colThree", ctypes.c_int), ]


class Sudoku:
    """
    Sudoku
    """

    def __init__(self, readData, writeData, procCallback):
        # typedef int (*SudokuReadData)(void* data, int row, int col);
        SudokuReadData = ctypes.CFUNCTYPE(ctypes.c_int,
                                          ctypes.c_void_p, ctypes.c_int, ctypes.c_int)

        def readDataCallback(data, row, col):
            return readData(row, col)

        # row col and value are in the range of 1-9
        # typedef void (*SudokuWriteData)(void* data, int row, int col, int value, SolveType type);
        SudokuWriteData = ctypes.CFUNCTYPE(
            None, ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int)

        def writeDataCallback(data, row, col, value, types):
            writeData(row, col, value, types)

        # typedef void (*SolveProcessCallback)(void* data, SolveProcedure* proc);
        SolveProcessCallback = ctypes.CFUNCTYPE(
            None, ctypes.c_void_p, ctypes.POINTER(SolveProcedure))

        def solveProcCallback(data, proc):
            if procCallback == None:
                return
            structProc = ctypes.cast(proc, ctypes.POINTER(SolveProcedure))
            procCallback(structProc)

        self.handler = libsudoku.CreateSudoku(SudokuReadData(readDataCallback), SudokuWriteData(
            writeDataCallback), SolveProcessCallback(solveProcCallback), None)

    def __del__(self):
        print("Destroy Sudoku")
        libsudoku.DestroySudoku(self.handler)

    def VerifySudoku(self):
        return libsudoku.VerifySudoku(self.handler)

    def GetKnownCount(self):
        return libsudoku.GetKnownCount(self.handler)

    def MakeResultString(self):
        RESULT_BUFFER_SIZE = (9 * 9 * 2 + 9 * 2 + 9 + 2 + 1)
        buffer = ctypes.create_string_buffer(RESULT_BUFFER_SIZE)
        libsudoku.MakeResultString(self.handler, buffer, RESULT_BUFFER_SIZE)
        return repr(buffer.value)

    def CalculateSudokuAll(self, dancing, callback):
        # typedef void (*SudokuAnswerCallback)(void* data, const char* ans);
        SudokuAnswerCallback = ctypes.CFUNCTYPE(
            None, ctypes.c_void_p, ctypes.c_void_p)

        def answerCallback(data, answer):
            if callback == None:
                return
            ans = ctypes.string_at(answer)
            callback(ans)
        return libsudoku.CalculateSudokuAll(self.handler, dancing, SudokuAnswerCallback(answerCallback), self.handler)


def VerifySudokuBoard(board):
    def ListToCArray(board):
        arrayType = ctypes.c_int * len(board)
        cboard = arrayType(*board)
        return cboard
    return libsudoku.VerifySudokuBoard(ListToCArray(board))


def SolveTypeName(types):
    return ctypes.string_at(libsudoku.SolveTypeName(types))


def ImproveTypeName(types):
    return ctypes.string_at(libsudoku.ImproveTypeName(types))
