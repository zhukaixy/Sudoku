const refArray = require("ref-array");
const intArray = refArray("int");
const refStruct = require("ref-struct");

const libSudoku = require("./libsudoku");
const solveProcedure = refStruct({
  type: "int",
  gridOneX: "int", // [1, 9]
  gridOneY: "int",
  gridTwoX: "int",
  gridTwoY: "int",
  gridThreeX: "int",
  gridThreeY: "int",
  numberOne: "int", // [1, 9]
  numberTwo: "int",
  numberThree: "int",
  panelRow: "int", // [1, 3]
  panelCol: "int",
  number: "int", // [1, 9]
  line: "int", // [1, 9]
  rowOne: "int", // [1, 9]
  rowTwo: "int",
  rowThree: "int",
  colOne: "int",
  colTwo: "int",
  colThree: "int"
});
const ref = require("ref");
const solveProcedurePtr = ref.refType(solveProcedure);

module.exports = {
  CreateSudoku: function(readFunc, writeFunc, procFunc) {
    const ffi = require("ffi");
    // typedef int (*SudokuReadData)(void* data, int row, int col);
    const wrapReadFunc = ffi.Callback(
      "int",
      ["pointer", "int", "int"],
      function(data, row, col) {
        return readFunc(row, col);
      }
    );
    // typedef void (*SudokuWriteData)(void* data, int row, int col, int value, SolveType type);
    const wrapWriteFunc = ffi.Callback(
      "void",
      ["pointer", "int", "int", "int", "int"],
      function(data, row, col, value, type) {
        writeFunc(row, col, value, type);
      }
    );
    // typedef void (*SolveProcessCallback)(void* data, SolveProcedure* proc);
    const wrapProcFunc = ffi.Callback(
      "void",
      ["pointer", solveProcedurePtr],
      function(data, proc) {
        if (procFunc == null) {
          return;
        }
        const procStruct = new solveProcedure(proc);
        procFunc(procStruct);
      }
    );
    return {
      handler: libSudoku.CreateSudoku(
        wrapReadFunc,
        wrapWriteFunc,
        wrapProcFunc,
        wrapProcFunc
      ),
      DestroySudoku: function() {
        libSudoku.DestroySudoku(this.handler);
      },
      VerifySudoku: function() {
        return libSudoku.VerifySudoku(this.handler);
      },
      GetKnownCount: function() {
        return libSudoku.GetKnownCount(this.handler);
      },
      MakeResultString: function() {
        const RESULT_BUFFER_SIZE = 9 * 9 * 2 + 9 * 2 + 9 + 2 + 1;
        const buffer = new Buffer(RESULT_BUFFER_SIZE);
        libSudoku.MakeResultString(this.handler, buffer, RESULT_BUFFER_SIZE);
        return ref.readCString(buffer, 0);
      },
      CalculateSudokuAll: function(dancing, callback) {
        // typedef void (*SudokuAnswerCallback)(void* data, const char* ans);
        const wrapCallback = ffi.Callback(
          "void",
          ["pointer", "string"],
          function(data, ans) {
            if (callback == null) {
              return;
            }
            callback(ans);
          }
        );
        return libSudoku.CalculateSudokuAll(
          this.handler,
          dancing,
          wrapCallback,
          this.handler
        );
      }
    };
  },
  VerifySudokuBoard: function(board) {
    const boardArray = new intArray(board);
    return libSudoku.VerifySudokuBoard(boardArray.buffer);
  },
  SolveTypeName: function(type) {
    return libSudoku.SolveTypeName(type);
  },
  ImproveTypeName: function(type) {
    return libSudoku.ImproveTypeName(type);
  },
  SolveType: {
    None: 0,
    GridOnlyOnePosibility: 1,
    RowNumberOnlyOneGrid: 2,
    ColNumberOnlyOneGrid: 3,
    BlockNumberOnlyOneGrid: 4
  },
  ImproveType: {
    DoNotImprove: 0,

    Row2GridWith2Posibility: 1,
    Col2GridWith2Posibility: 2,
    Block2GridWith2Posibility: 3,

    Row3GridWith3Posibility: 4,
    Col3GridWith3Posibility: 5,
    Block3GridWith3Posibility: 6,

    Row2NumberIn2Grid: 7,
    Col2NumberIn2Grid: 8,
    Block2NumberIn2Grid: 9,

    Row3NumberIn3Grid: 10,
    Col3NumberIn3Grid: 11,
    Block3NumberIn3Grid: 12,

    InBlockNumberInOneRow: 13,
    InBlockNumberInOneCol: 14,

    InRowNumberInBlock: 15,
    InColNumberInBlock: 16,

    TwoRowOneNumberInTwoCol: 17,
    TwoColOneNumberInTwoRow: 18,

    ThreeRowOneNumberInThreeCol: 19,
    ThreeColOneNumberInThreeRow: 20
  }
};
