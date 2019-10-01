import sudoku


def DoNotImprove(proc):
    return "Do Not Improve"


def GridWithPosibility2(proc):
    return "gridOne: %d %d, gridTwo: %d %d, value: %d %d" % (
        proc.gridOneX,
        proc.gridOneY,
        proc.gridTwoX,
        proc.gridTwoY,
        proc.numberOne,
        proc.numberTwo)


def GridWithPosibility3(proc):
    return "gridOne: %d %d, gridTwo: %d %d, gridThree: %d %d, value: %d %d %d" % (
        proc.gridOneX,
        proc.gridOneY,
        proc.gridTwoX,
        proc.gridTwoY,
        proc.gridThreeX,
        proc.gridThreeY,
        proc.numberOne,
        proc.numberTwo,
        proc.numberThree)


def NumberInGrid2(proc):
    return "value: %d %d, gridOne: %d %d, gridTwo: %d %d" % (
        proc.numberOne,
        proc.numberTwo,
        proc.gridOneX,
        proc.gridOneY,
        proc.gridTwoX,
        proc.gridTwoY)


def NumberInGrid3(proc):
    return "value: %d %d %d, gridOne: %d %d, gridTwo: %d %d, gridThree: %d %d" % (
        proc.numberOne,
        proc.numberThree,
        proc.numberTwo,
        proc.gridOneX,
        proc.gridOneY,
        proc.gridTwoX,
        proc.gridTwoY,
        proc.gridThreeX,
        proc.gridThreeY)


def BlockNumberInRowCol(proc):
    return "block: %d %d, value: %d, line: %d" % (proc.panelRow, proc.panelCol, proc.number, proc.line)


def RowColNumberInBlock(proc):
    return "line: % d, value: % d, block: % d % d" % (proc.line, proc.number, proc.panelRow, proc.panelCol)


def TwoRowOneNumberInTwoCol(proc):
    return "row: % d % d, value: % d, column: % d % d" % (
        proc.rowOne,
        proc.rowTwo,
        proc.number,
        proc.colOne,
        proc.colTwo)


def TwoColOneNumberInTwoRow(proc):
    return "column: % d % d, value: % d, row: % d % d" % (
        proc.colOne,
        proc.colTwo,
        proc.number,
        proc.rowOne,
        proc.rowTwo)


def ThreeRowOneNumberInThreeCol(proc):
    return "row: % d % d % d, value: % d, column: % d % d % d" % (
        proc.rowOne,
        proc.rowTwo,
        proc.rowThree,
        proc.number,
        proc.colOne,
        proc.colTwo,
        proc.colThree)


def ThreeColOneNumberInThreeRow(proc):
    return "column: % d % d % d, value: % d, row: % d % d % d" % (
        proc.colOne,
        proc.colTwo,
        proc.colThree,
        proc.number,
        proc.rowOne,
        proc.rowTwo,
        proc.rowThree)


AllImproveFunctions = [
    DoNotImprove,
    GridWithPosibility2,
    GridWithPosibility2,
    GridWithPosibility2,
    GridWithPosibility3,
    GridWithPosibility3,
    GridWithPosibility3,
    NumberInGrid2,
    NumberInGrid2,
    NumberInGrid2,
    NumberInGrid3,
    NumberInGrid3,
    NumberInGrid3,
    BlockNumberInRowCol,
    BlockNumberInRowCol,
    RowColNumberInBlock,
    RowColNumberInBlock,
    TwoRowOneNumberInTwoCol,
    TwoColOneNumberInTwoRow,
    ThreeRowOneNumberInThreeCol,
    ThreeColOneNumberInThreeRow
]


# def solveProcess(proc):
#     print("Improve: %s %s" % (sudoku.ImproveTypeName(
#         proc.type), AllImproveFunctions[proc.types](proc)))
