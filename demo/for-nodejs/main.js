const boolMatrix = require("./boolmatrix");

const row1 = [0, 3, 6];
const row2 = [0, 3];
const row3 = [3, 4, 6];
const row4 = [2, 4, 5];
const row5 = [1, 2, 5, 6];
const row6 = [1, 6];

const matrix = boolMatrix.CreateBoolMatrix(6, 7, 17);
matrix.SetMatrixRowData(row1);
matrix.SetMatrixRowData(row2);
matrix.SetMatrixRowData(row3);
matrix.SetMatrixRowData(row4);
matrix.SetMatrixRowData(row5);
matrix.SetMatrixRowData(row6);
const count = matrix.DancingLinks(false, answer => {
  console.log("BoolMatrixAnswer:", answer);
});
matrix.DestroyBoolMatrix();
console.log("BoolMatrix Answer Count:", count);
