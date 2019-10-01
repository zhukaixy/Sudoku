<?php

class BoolMatrix
{
	private $handler = NULL;
	public static $callback;
	function __construct($rows, $cols, $maxNodes)
	{
		$this->handler = PHPCreateBoolMatrix($rows, $cols, $maxNodes);
	}
	function __destruct()
	{
		printf("Destroy Bool Matrix\n");
		PHPDestroyBoolMatrix($this->handler);
	}
	function SetMatrixRowData($row)
	{
		PHPSetMatrixRowData($this->handler, $row);
	}
	function DancingLinks($justOne, Closure $callback)
	{
		BoolMatrix::$callback = $callback;
		return PHPDancingLinks($this->handler, $justOne);
	}
}

function MatrixAnswerCallback($answer)
{
	if (BoolMatrix::$callback != NULL) {
		call_user_func(BoolMatrix::$callback, $answer);
	}
}
