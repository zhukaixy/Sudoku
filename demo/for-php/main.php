<?php

require("./boolmatrix.php");

$matrix = new BoolMatrix(6, 7, 17);
$matrix->SetMatrixRowData(array(0, 3, 6));
$matrix->SetMatrixRowData(array(0, 3));
$matrix->SetMatrixRowData(array(3, 4, 6));
$matrix->SetMatrixRowData(array(2, 4, 5));
$matrix->SetMatrixRowData(array(1, 2, 5, 6));
$matrix->SetMatrixRowData(array(1, 6));
$count = $matrix->DancingLinks(false, function($answer){
	echo "BoolMatrixAnswer: ".json_encode($answer)."\n";
});
echo "BoolMatrix Answer Count: $count\n";
