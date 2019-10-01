<?php

function BoolMatrixUsage()
{
	require("./boolmatrix.php");

	$matrix = new BoolMatrix(6, 7, 17);
	$matrix->SetMatrixRowData(array(0, 3, 6));
	$matrix->SetMatrixRowData(array(0, 3));
	$matrix->SetMatrixRowData(array(3, 4, 6));
	$matrix->SetMatrixRowData(array(2, 4, 5));
	$matrix->SetMatrixRowData(array(1, 2, 5, 6));
	$matrix->SetMatrixRowData(array(1, 6));
	$count = $matrix->DancingLinks(false, function ($answer) {
		printf("BoolMatrixAnswer: %s\n", json_encode($answer)); // PHP_EOL
	});
	printf("BoolMatrix Answer Count: %d\n", $count);
}

function OpenFileForRead($path)
{
	$file = fopen($path, "r");
	if ($file == false) {
		fprintf(STDERR, "Error: open file %s failed\n", $path);
	}
	return $file;
}

function GetSudokuFromFile($file)
{
	$BOARD_SIZE = (9 * 9);
	$count = 0;
	$sudo = [];
	for (; $count < $BOARD_SIZE;) {
		if (feof($file)) {
			return false;
		}
		$c = fread($file, 1);
		if ($c >= '0' && $c <= '9') {
			$sudo[$count] = $c - '0';
			$count++;
		}
	}
	return $sudo;
}

function DisplaySudoku($sudo)
{
	for ($i = 0; $i < 9; $i++) {
		for ($j = 0; $j < 9; $j++) {
			$index = $i * 9 + $j;
			printf("%d ", $sudo[$index]);
			if ($j == 2 || $j == 5) {
				printf(" ");
			}
		}
		printf("\n");
		if ($i == 2 || $i == 5) {
			printf("\n");
		}
	}
}

function Usage($exec)
{
	printf("Usage: %s <file>\n", $exec);
	printf("\t<file>: The sudoku file path\n");
	printf("\tor using %s with stdin\n", $exec);
}

// Main Function Start

BoolMatrixUsage();

if ($argc != 1 && $argc != 2) {
	Usage($argv[0]);
	exit(-1);
}
$file = STDIN;
if ($argc == 2) {
	$file = false;
	$file = OpenFileForRead($argv[1]);
	if ($file == false) {
		Usage($argv[0]);
		exit(-1);
	}
}
$board = [];
if (($board = GetSudokuFromFile($file)) == false) {
	fprintf(STDERR, "Read sudoku failed" . PHP_EOL);
	Usage($argv[0]);
	fclose($file);
	exit(-1);
}
$board_dancing = [];
$BOARD_SIZE = (9 * 9);
for ($i = 0; $i < $BOARD_SIZE; $i++) {
	$board_dancing[$i] = $board[$i];
}

require("./sudoku.php"); {
	require("./solveproc.php");
	$sudo = new Sudoku(function ($row, $col) {
		global $board;
		$index = ($row - 1) * 9 + $col - 1;
		return $board[$index];
	}, function ($row, $col, $value, $type) {
		global $board;
		$index = ($row - 1) * 9 + $col - 1;
		$board[$index] = $value;
		printf("Solve: %s row:%d column:%d value:%d\n", Sudoku::SolveTypeName($type), $row, $col, $value);
	}, GetSolveDisplayClousre());
	$count = $sudo->GetKnownCount();
	printf("Sudoku Known Count: %d\n", $count);
	printf("Calculate step by step\n");
	$num = $sudo->CalculateSudokuAll(false, function ($ans) { });
	printf("Answer Count: %d\n", $num);
	DisplaySudoku($board);
	$status = Sudoku::VerifySudokuBoard($board);
	printf("Verify: %s\n", $status ? "True" : "False");
} {
	$sudo = new Sudoku(function ($row, $col) {
		global $board_dancing;
		$index = ($row - 1) * 9 + $col - 1;
		return $board_dancing[$index];
	}, function ($row, $col, $value, $type) {
		global $board_dancing;
		$index = ($row - 1) * 9 + $col - 1;
		$board_dancing[$index] = $value;
	}, function ($proc) { });
	printf("Calculate using dancing\n");
	$num = $sudo->CalculateSudokuAll(True, function ($ans) { });
	printf("Answer Count: %d\n", $num);
	printf("One of it:\n");
	DisplaySudoku($board_dancing);
	$status = Sudoku::VerifySudokuBoard($board_dancing);
	printf("Verify: %s\n", $status ? "True" : "False");
}
