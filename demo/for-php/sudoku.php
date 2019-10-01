<?php

class Sudoku
{
	private $handler = NULL;
	public static $readData;
	public static $writeData;
	public static $procCallback;
	public static $answerCallback;
	function __construct(Closure $readData, Closure $writeData, Closure $procCallback)
	{
		Sudoku::$readData = $readData;
		Sudoku::$writeData = $writeData;
		Sudoku::$procCallback = $procCallback;
		$this->handler = PHPCreateSudoku();
	}
	function __destruct()
	{
		printf("Destroy Sudoku\n");
		PHPDestroySudoku($this->handler);
	}
	function VerifySudoku()
	{
		return PHPVerifySudoku($this->handler);
	}
	function GetKnownCount()
	{
		return PHPGetKnownCount($this->handler);
	}
	function MakeResultString()
	{
		return PHPMakeResultString($this->handler);
	}
	function CalculateSudokuAll($dancing, Closure $cb)
	{
		Sudoku::$answerCallback = $cb;
		return PHPCalculateSudokuAll($this->handler, $dancing);
	}
	static function VerifySudokuBoard($board)
	{
		return PHPVerifySudokuBoard($board);
	}
	static function SolveTypeName($type)
	{
		return PHPSolveTypeName($type);
	}
	static function ImproveTypeName($type)
	{
		return PHPImproveTypeName($type);
	}
}
function SudokuReadData($row, $col)
{
	if (Sudoku::$readData != NULL) {
		return call_user_func(Sudoku::$readData, $row, $col);
	}
	return 0;
}
function SudokuWriteData($row, $col, $value, $type)
{
	if (Sudoku::$writeData != NULL) {
		call_user_func(Sudoku::$writeData, $row, $col, $value, $type);
	}
}
function SudokuProcCallback($proc)
{
	if (Sudoku::$procCallback != NULL) {
		call_user_func(Sudoku::$procCallback, $proc);
	}
}
function SudokuAnswerCallback($answer)
{
	if (Sudoku::$answerCallback != NULL) {
		call_user_func(Sudoku::$answerCallback, $answer);
	}
}
