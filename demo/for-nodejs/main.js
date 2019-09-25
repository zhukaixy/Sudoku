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

// const Usage = function(exec) {
//   console.log("Usage: %s <file>", exec);
//   console.log("\t<file>: The sudoku file path");
//   console.log("\tor using %s with stdin", exec);
// };

// const fs = require("fs");
// const BOARD_SIZE = 9 * 9;
// const GetSudokuFromFile = function(file, sudo) {
//   const buf = new Buffer.alloc(1);
//   let count = 0;
//   for (; count < BOARD_SIZE; ) {
//     const c = fs.readSync(file, buf, 0, 1, null);
//     if (c == -1) {
//       return false;
//     }
//     const num = buf.readUInt8(0);
//     if (num >= 48 && num <= 57) {
//       sudo[count] = num - 48;
//       count++;
//     }
//   }
//   return true;
// };

// const DisplaySudoku = function(board) {
//   let output = "";
//   for (let i = 0; i < 9; i++) {
//     for (let j = 0; j < 9; j++) {
//       let index = i * 9 + j;
//       output += "" + board[index] + " ";
//       if (j == 2 || j == 5) {
//         output += " ";
//       }
//     }
//     output += "\n";
//     if (i == 2 || i == 5) {
//       output += "\n";
//     }
//   }
//   console.log(output);
// };

// const sudoku = require("./sudoku");
// const improveType = sudoku.ImproveType;
// const SudokuSolveProcess = function(proc) {
//   console.log("Improve: %s ", sudoku.ImproveTypeName(proc.type));
//   switch (proc.type) {
//     case improveType.DoNotImprove:
//       console.log("Do Not Improve");
//       break;

//     case improveType.Row2GridWith2Posibility:
//     case improveType.Col2GridWith2Posibility:
//     case improveType.Block2GridWith2Posibility:
//       console.log(
//         "gridOne: %d %d, gridTwo: %d %d, value: %d %d",
//         proc.gridOneX,
//         proc.gridOneY,
//         proc.gridTwoX,
//         proc.gridTwoY,
//         proc.numberOne,
//         proc.numberTwo
//       );
//       break;

//     case improveType.Row3GridWith3Posibility:
//     case improveType.Col3GridWith3Posibility:
//     case improveType.Block3GridWith3Posibility:
//       console.log(
//         "gridOne: %d %d, gridTwo: %d %d, gridThree: %d %d, value: %d %d %d",
//         proc.gridOneX,
//         proc.gridOneY,
//         proc.gridTwoX,
//         proc.gridTwoY,
//         proc.gridThreeX,
//         proc.gridThreeY,
//         proc.numberOne,
//         proc.numberTwo,
//         proc.numberThree
//       );
//       break;

//     case improveType.Row2NumberIn2Grid:
//     case improveType.Col2NumberIn2Grid:
//     case improveType.Block2NumberIn2Grid:
//       console.log(
//         "value: %d %d, gridOne: %d %d, gridTwo: %d %d",
//         proc.numberOne,
//         proc.numberTwo,
//         proc.gridOneX,
//         proc.gridOneY,
//         proc.gridTwoX,
//         proc.gridTwoY
//       );
//       break;

//     case improveType.Row3NumberIn3Grid:
//     case improveType.Col3NumberIn3Grid:
//     case improveType.Block3NumberIn3Grid:
//       console.log(
//         "value: %d %d %d, gridOne: %d %d, gridTwo: %d %d, gridThree: %d %d",
//         proc.numberOne,
//         proc.numberThree,
//         proc.numberTwo,
//         proc.gridOneX,
//         proc.gridOneY,
//         proc.gridTwoX,
//         proc.gridTwoY,
//         proc.gridThreeX,
//         proc.gridThreeY
//       );
//       break;

//     case improveType.InBlockNumberInOneRow:
//     case improveType.InBlockNumberInOneCol:
//       console.log(
//         "block: %d %d, value: %d, line: %d",
//         proc.panelRow,
//         proc.panelCol,
//         proc.number,
//         proc.line
//       );
//       break;

//     case improveType.InRowNumberInBlock:
//     case improveType.InColNumberInBlock:
//       console.log(
//         "line: %d, value: %d, block: %d %d",
//         proc.line,
//         proc.number,
//         proc.panelRow,
//         proc.panelCol
//       );
//       break;

//     case improveType.TwoRowOneNumberInTwoCol:
//       console.log(
//         "row: %d %d, value: %d, column: %d %d",
//         proc.rowOne,
//         proc.rowTwo,
//         proc.number,
//         proc.colOne,
//         proc.colTwo
//       );
//       break;
//     case improveType.TwoColOneNumberInTwoRow:
//       console.log(
//         "column: %d %d, value: %d, row: %d %d",
//         proc.colOne,
//         proc.colTwo,
//         proc.number,
//         proc.rowOne,
//         proc.rowTwo
//       );
//       break;

//     case improveType.ThreeRowOneNumberInThreeCol:
//       console.log(
//         "row: %d %d %d, value: %d, column: %d %d %d",
//         proc.rowOne,
//         proc.rowTwo,
//         proc.rowThree,
//         proc.number,
//         proc.colOne,
//         proc.colTwo,
//         proc.colThree
//       );
//       break;
//     case improveType.ThreeColOneNumberInThreeRow:
//       console.log(
//         "column: %d %d %d, value: %d, row: %d %d %d",
//         proc.colOne,
//         proc.colTwo,
//         proc.colThree,
//         proc.number,
//         proc.rowOne,
//         proc.rowTwo,
//         proc.rowThree
//       );
//       break;
//     default:
//       console.log("Do Not To Here: Default");
//       break;
//   }
// };

// const argv = process.argv;
// const argc = argv.length;

// if (argc != 2 && argc != 3) {
//   Usage("node main.js");
//   process.exit(-1);
// }

// let fd = process.stdin.fd;
// if (argc == 3) {
//   fd = fs.openSync(argv[2], "r");
// }

// let board = [];
// if (GetSudokuFromFile(fd, board) == false) {
//   console.error("Read sudoku from %s failed", argv[2]);
//   process.exit(-1);
// }
// const board_dancing = { ...board };

// const sudo = sudoku.CreateSudoku(
//   (row, col) => {
//     const index = (row - 1) * 9 + col - 1;
//     return board[index];
//   },
//   (row, col, value, type) => {
//     console.log(
//       "Solve: %s row:%d column:%d value:%d",
//       sudoku.SolveTypeName(type),
//       row,
//       col,
//       value
//     );
//     const index = (row - 1) * 9 + col - 1;
//     board[index] = value;
//   },
//   SudokuSolveProcess
// );
// const cnt = sudo.GetKnownCount();
// console.log("Sudoku Known Count: %d", cnt);
// console.log("Calculate step by step");
// const num = sudo.CalculateSudokuAll(true, () => {});
// console.log("Answer Count: %d", num);
// DisplaySudoku(board);
// const status = sudoku.VerifySudokuBoard(board);
// console.log("Verify: %s", status ? "True" : "False");
