var ref = require("ref");
var refArray = require("ref-array");
var ffi = require("ffi");

// typedef
var voidPtr = ref.refType("void");
var boolMatrixPtr = ref.refType("void");
var intArray = refArray("int");

var libsudoku = ffi.Library("libsudoku", {
  CreateBoolMatrix: [boolMatrixPtr, ["int", "int", "int"]],
  DestroyBoolMatrix: ["void", [boolMatrixPtr]],
  SetMatrixRowData: ["void", [boolMatrixPtr, intArray, "int"]],
  DancingLinks: ["int", [boolMatrixPtr, "bool", voidPtr, voidPtr]]
});

module.exports = libsudoku;
