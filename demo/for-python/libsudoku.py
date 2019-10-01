import platform
import ctypes

dylibName = ""
arch = platform.system()
if arch == "Darwin":
    dylibName = "libsudoku.dylib"
elif arch == "Linux":
    dylibName = "libsudoku.so"
else:
    dylibName = "sudoku.dll"

handler = ctypes.CDLL(dylibName)

CreateBoolMatrix = handler.CreateBoolMatrix
CreateBoolMatrix.restype = ctypes.c_void_p
CreateBoolMatrix.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]

DestroyBoolMatrix = handler.DestroyBoolMatrix
DestroyBoolMatrix.restype = None
DestroyBoolMatrix.argtypes = [ctypes.c_void_p]

SetMatrixRowData = handler.SetMatrixRowData
SetMatrixRowData.restype = None
SetMatrixRowData.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int]

DancingLinks = handler.DancingLinks
DancingLinks.restype = ctypes.c_int
DancingLinks.argtypes = [ctypes.c_void_p,
                         ctypes.c_bool, ctypes.c_void_p, ctypes.c_void_p]


# CreateSudoku = handler.CreateSudoku
# CreateSudoku.restype = ctypes.c_void_p
# CreateSudoku.argtypes = [ctypes.c_void_p,
#                          ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p]

# DestroySudoku = handler.DestroySudoku
# DestroySudoku.restype = None
# DestroySudoku.argtypes = [ctypes.c_void_p]

# VerifySudoku = handler.VerifySudoku
# VerifySudoku.restype = ctypes.c_bool
# VerifySudoku.argtypes = [ctypes.c_void_p]

# GetKnownCount = handler.GetKnownCount
# GetKnownCount.restype = ctypes.c_int
# GetKnownCount.argtypes = [ctypes.c_void_p]

# MakeResultString = handler.MakeResultString
# MakeResultString.restype = None
# MakeResultString.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int]

# CalculateSudokuAll = handler.CalculateSudokuAll
# CalculateSudokuAll.restype = ctypes.c_int
# CalculateSudokuAll.argtypes = [ctypes.c_void_p,
#                                ctypes.c_bool, ctypes.c_void_p, ctypes.c_void_p]


# VerifySudokuBoard = handler.VerifySudokuBoard
# VerifySudokuBoard.restype = ctypes.c_bool
# VerifySudokuBoard.argtypes = [ctypes.c_void_p]

# SolveTypeName = handler.SolveTypeName
# SolveTypeName.restype = ctypes.c_void_p
# SolveTypeName.argtypes = [ctypes.c_int]

# ImproveTypeName = handler.ImproveTypeName
# ImproveTypeName.restype = ctypes.c_void_p
# ImproveTypeName.argtypes = [ctypes.c_int]
