const libSudoku = require("./libsudoku");
const refArray = require("ref-array");
const intArray = refArray("int");

module.exports = {
  CreateBoolMatrix: function(rows, cols, maxNodes) {
    return {
      handler: libSudoku.CreateBoolMatrix(rows, cols, maxNodes),
      SetMatrixRowData: function(row) {
        const rowArray = new intArray(row);
        libSudoku.SetMatrixRowData(
          this.handler,
          rowArray.buffer,
          rowArray.length
        );
      },
      DancingLinks: function(onlyOne, callback) {
        const ffi = require("ffi");
        // typedef void (*AnswerCallback)(void* data, const int* answer, int size);
        const wrapCallback = ffi.Callback(
          "void",
          ["pointer", intArray, "int"],
          function(data, answer, size) {
            let arrayBuffer = [];
            for (let i = 0; i < size; i++) {
              const num = answer[i];
              arrayBuffer.push(num + 1);
            }
            callback(arrayBuffer);
          }
        );
        return libSudoku.DancingLinks(
          this.handler,
          onlyOne,
          wrapCallback,
          this.handler
        );
      },
      DestroyBoolMatrix: function() {
        libSudoku.DestroyBoolMatrix(this.handler);
      }
    };
  }
};
