const ffi = require("ffi");

const refArray = require("ref-array");
const intArray = refArray("int");

const libsudoku = ffi.Library("libsudoku", {
  CreateBoolMatrix: ["pointer", ["int", "int", "int"]],
  DestroyBoolMatrix: ["void", ["pointer"]],
  SetMatrixRowData: ["void", ["pointer", intArray, "int"]],
  DancingLinks: ["int", ["pointer", "bool", "pointer", "pointer"]],

  CreateSudoku: ["pointer", ["pointer", "pointer", "pointer", "pointer"]],
  DestroySudoku: ["void", ["pointer"]],
  VerifySudoku: ["bool", ["pointer"]],
  GetKnownCount: ["int", ["pointer"]],
  MakeResultString: ["void", ["pointer", "pointer", "int"]],
  CalculateSudokuAll: ["int", ["pointer", "bool", "pointer", "pointer"]],

  VerifySudokuBoard: ["bool", [intArray]],
  SolveTypeName: ["string", ["int"]],
  ImproveTypeName: ["string", ["int"]]
});

module.exports = libsudoku;
