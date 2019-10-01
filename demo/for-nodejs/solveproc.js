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

// module.exports = SudokuSolveProcess;
