const BoolMatrixUsage = function() {
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
  console.log("BoolMatrix Answer Count: %d", count);
};

const fs = require("fs");
const BOARD_SIZE = 9 * 9;

const OpenFileForRead = function(path) {
  return fs.openSync(path, "r");
};
const GetSudokuFromFile = function(file, sudo) {
  const buf = new Buffer.alloc(1);
  let count = 0;
  for (; count < BOARD_SIZE; ) {
    const c = fs.readSync(file, buf, 0, 1, null);
    if (c == -1) {
      return false;
    }
    const num = buf.readUInt8(0);
    if (num >= 48 && num <= 57) {
      sudo[count] = num - 48;
      count++;
    }
  }
  return true;
};

const DisplaySudoku = function(board) {
  let output = "";
  for (let i = 0; i < 9; i++) {
    for (let j = 0; j < 9; j++) {
      let index = i * 9 + j;
      output += "" + board[index] + " ";
      if (j == 2 || j == 5) {
        output += " ";
      }
    }
    output += "\n";
    if (i == 2 || i == 5) {
      output += "\n";
    }
  }
  console.log(output);
};

const Usage = function(exec) {
  console.log("Usage: %s <file>", exec);
  console.log("\t<file>: The sudoku file path");
  console.log("\tor using %s with stdin", exec);
};

// Main Function Start

BoolMatrixUsage();

const argv = process.argv;
const argc = argv.length;

if (argc != 2 && argc != 3) {
  Usage("node main.js");
  process.exit(-1);
}

let fd = process.stdin.fd;
if (argc == 3) {
  try {
    fd = OpenFileForRead(argv[2]);
  } catch (e) {
    console.log(e);
    Usage("node main.js");
    process.exit(-1);
  }
}

let board = [];
if (GetSudokuFromFile(fd, board) == false) {
  console.error("Read sudoku from %s failed", argv[2]);
  process.exit(-1);
}
let board_dancing = [];
for (let i = 0; i < 81; i++) {
  board_dancing[i] = board[i];
}

// const sudoku = require("./sudoku");
// const solveproc = require("./solveproc");
// const sudo = sudoku.CreateSudoku(
//   (row, col) => {
//     const index = (row - 1) * 9 + col - 1;
//     return board[index];
//   },
//   (row, col, value, type) => {
//     const index = (row - 1) * 9 + col - 1;
//     board[index] = value;
//     // if we call sudoku.SolveTypeName, node will crash, i don't know why
//     // console.log(
//     //   "Solve: %s row:%d column:%d value:%d",
//     //   sudoku.SolveTypeName(type),
//     //   row,
//     //   col,
//     //   value
//     // );
//   },
//   solveproc.SudokuSolveProcess
// );
// const cnt = sudo.GetKnownCount();
// console.log("Sudoku Known Count: %d", cnt);
// console.log("Calculate step by step");
// const num = sudo.CalculateSudokuAll(false, null);
// console.log("Answer Count: %d", num);
// DisplaySudoku(board);
// const status = sudoku.VerifySudokuBoard(board);
// console.log("Verify: %s", status ? "True" : "False");
// sudo.DestroySudoku();

// const sudo_dancing = sudoku.CreateSudoku(
//   (row, col) => {
//     const index = (row - 1) * 9 + col - 1;
//     return board_dancing[index];
//   },
//   (row, col, value, type) => {
//     const index = (row - 1) * 9 + col - 1;
//     board_dancing[index] = value;
//   },
//   null
// );
// console.log("Calculate using dancing");
// const num_dancing = sudo_dancing.CalculateSudokuAll(true, null);
// console.log("Answer Count: %d", num_dancing);
// console.log("One of it:");
// DisplaySudoku(board_dancing);
// const status_dancing = sudoku.VerifySudokuBoard(board_dancing);
// console.log("Verify: %s\n", status_dancing ? "True" : "False");
// sudo_dancing.DestroySudoku();

DisplaySudoku(board);
