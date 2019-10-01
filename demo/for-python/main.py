import sys
import boolmatrix
import sudoku
import solveproc


def BoolMatrixUsage():
    row1 = [0, 3, 6]
    row2 = [0, 3]
    row3 = [3, 4, 6]
    row4 = [2, 4, 5]
    row5 = [1, 2, 5, 6]
    row6 = [1, 6]

    matrix = boolmatrix.BoolMatrix(6, 7, 17)
    matrix.SetMatrixRowData(row1)
    matrix.SetMatrixRowData(row2)
    matrix.SetMatrixRowData(row3)
    matrix.SetMatrixRowData(row4)
    matrix.SetMatrixRowData(row5)
    matrix.SetMatrixRowData(row6)

    def Answer(answer):
        print("BoolMatrixAnswer:", answer)

    count = matrix.DancingLinks(False, Answer)
    print("BoolMatrix Answer Count: %d" % (count))


def OpenFileForRead(path):
    try:
        return open(path)
    except OSError:
        sys.stderr.write("Error: open file %s failed\n" % (path))
        return None


def GetSudokuFromFile(file, board):
    try:
        BOARD_SIZE = (9*9)
        count = 0
        while count < BOARD_SIZE:
            c = file.read(1)
            if c >= '0' and c <= '9':
                board.append(int(c))
                # board[count] = int(c)
                count += 1
        return True
    except EOFError:
        return False


def DisplaySudoku(board):
    board_string = ""
    for i in range(9):
        for j in range(9):
            index = i * 9 + j
            board_string += "%d " % (board[index])
            if j == 2 or j == 5:
                board_string += " "
        board_string += "\n"
        if i == 2 or i == 5:
            board_string += "\n"
    print(board_string)


def Usage(exec):
    print("Usage: %s <file>" % (exec))
    print("\t<file>: The sudoku file path")
    print("\tor using %s with stdin" % (exec))


# Main Function Start

BoolMatrixUsage()

argv = sys.argv
argc = len(argv)

if argc != 1 and argc != 2:
    Usage(argv[0])
    sys.exit(-1)

file = sys.stdin
if argc == 2:
    file = OpenFileForRead(argv[1])
    if file == None:
        Usage(argv[0])
        sys.exit(-1)


board = []
if GetSudokuFromFile(file, board) == False:
    sys.stderr.write("Read sudoku from %s failed" % (argv[1]))
    sys.exit(-1)
board_dancing = []
for i in range(81):
    board_dancing.append(board[i])


# def readData(row, col):
#     index = (row - 1) * 9 + col - 1
#     return board[index]


# def writeData(row, col, value, types):
#     index = (row - 1) * 9 + col - 1
#     board[index] = value
#     print("Solve: %s row:%d column:%d value:%d" %
#           (sudoku.SolveTypeName(types), row, col, value))


# sudo = sudoku.Sudoku(readData, writeData, solveproc.solveProcess)
# cnt = sudo.GetKnownCount()
# print("Sudoku Known Count: %d" % (cnt))
# # print("Calculate step by step")
# # num = sudo.CalculateSudokuAll(False, None)
# # print("Answer Count: %d" % (num))
# DisplaySudoku(board)
# status = sudoku.VerifySudokuBoard(board)
# statusStr = "False"
# if status:
#     statusStr = "True"
# print("Verify: %s" % (statusStr))


# def readDataDancing(row, col):
#     index = (row - 1) * 9 + col - 1
#     return board_dancing[index]


# def writeDataDancing(row, col, value, types):
#     index = (row - 1) * 9 + col - 1
#     board_dancing[index] = value


# sudo_dancing = sudoku.Sudoku(readDataDancing, writeDataDancing, None)
# # print("Calculate using dancing")
# # num = sudo_dancing.CalculateSudokuAll(True, None)
# # print("Answer Count: %d" % (num))
# print("One of it:")
# DisplaySudoku(board_dancing)
# status = sudoku.VerifySudokuBoard(board_dancing)
# statusStr = "False"
# if status:
#     statusStr = "True"
# print("Verify: %s" % (statusStr))

DisplaySudoku(board)
