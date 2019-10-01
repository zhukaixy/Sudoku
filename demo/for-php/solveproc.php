<?php

const DoNotImprove = 0;

const Row2GridWith2Posibility = 1;
const Col2GridWith2Posibility = 2;
const Block2GridWith2Posibility = 3;

const Row3GridWith3Posibility = 4;
const Col3GridWith3Posibility = 5;
const Block3GridWith3Posibility = 6;

const Row2NumberIn2Grid = 7;
const Col2NumberIn2Grid = 8;
const Block2NumberIn2Grid = 9;

const Row3NumberIn3Grid = 10;
const Col3NumberIn3Grid = 11;
const Block3NumberIn3Grid = 12;

const InBlockNumberInOneRow = 13;
const InBlockNumberInOneCol = 14;

const InRowNumberInBlock = 15;
const InColNumberInBlock = 16;

const TwoRowOneNumberInTwoCol = 17;
const TwoColOneNumberInTwoRow = 18;

const ThreeRowOneNumberInThreeCol = 19;
const ThreeColOneNumberInThreeRow = 20;

function GetSolveDisplayClousre()
{
	return function ($proc) {
		printf("Improve: %s ", Sudoku::ImproveTypeName($proc["type"]));
		switch ($proc["type"]) {
			case DoNotImprove:
				printf("Do Not Improve\n");
				break;

			case Row2GridWith2Posibility:
			case Col2GridWith2Posibility:
			case Block2GridWith2Posibility:
				printf(
					"gridOne: %d %d, gridTwo: %d %d, value: %d %d\n",
					$proc["gridOneX"],
					$proc["gridOneY"],
					$proc["gridTwoX"],
					$proc["gridTwoY"],
					$proc["numberOne"],
					$proc["numberTwo"]
				);
				break;

			case Row3GridWith3Posibility:
			case Col3GridWith3Posibility:
			case Block3GridWith3Posibility:
				printf(
					"gridOne: %d %d, gridTwo: %d %d, gridThree: %d %d, value: %d %d %d\n",
					$proc["gridOneX"],
					$proc["gridOneY"],
					$proc["gridTwoX"],
					$proc["gridTwoY"],
					$proc["gridThreeX"],
					$proc["gridThreeY"],
					$proc["numberOne"],
					$proc["numberTwo"],
					$proc["numberThree"]
				);
				break;

			case Row2NumberIn2Grid:
			case Col2NumberIn2Grid:
			case Block2NumberIn2Grid:
				printf(
					"value: %d %d, gridOne: %d %d, gridTwo: %d %d\n",
					$proc["numberOne"],
					$proc["numberTwo"],
					$proc["gridOneX"],
					$proc["gridOneY"],
					$proc["gridTwoX"],
					$proc["gridTwoY"]
				);
				break;

			case Row3NumberIn3Grid:
			case Col3NumberIn3Grid:
			case Block3NumberIn3Grid:
				printf(
					"value: %d %d %d, gridOne: %d %d, gridTwo: %d %d, gridThree: %d %d\n",
					$proc["numberOne"],
					$proc["numberThree"],
					$proc["numberTwo"],
					$proc["gridOneX"],
					$proc["gridOneY"],
					$proc["gridTwoX"],
					$proc["gridTwoY"],
					$proc["gridThreeX"],
					$proc["gridThreeY"]
				);
				break;

			case InBlockNumberInOneRow:
			case InBlockNumberInOneCol:
				printf("block: %d %d, value: %d, line: %d\n", $proc["panelRow"], $proc["panelCol"], $proc["number"], $proc["line"]);
				break;

			case InRowNumberInBlock:
			case InColNumberInBlock:
				printf("line: %d, value: %d, block: %d %d\n", $proc["line"], $proc["number"], $proc["panelRow"], $proc["panelCol"]);
				break;

			case TwoRowOneNumberInTwoCol:
				printf(
					"row: %d %d, value: %d, column: %d %d\n",
					$proc["rowOne"],
					$proc["rowTwo"],
					$proc["number"],
					$proc["colOne"],
					$proc["colTwo"]
				);
				break;
			case TwoColOneNumberInTwoRow:
				printf(
					"column: %d %d, value: %d, row: %d %d\n",
					$proc["colOne"],
					$proc["colTwo"],
					$proc["number"],
					$proc["rowOne"],
					$proc["rowTwo"]
				);
				break;

			case ThreeRowOneNumberInThreeCol:
				printf(
					"row: %d %d %d, value: %d, column: %d %d %d\n",
					$proc["rowOne"],
					$proc["rowTwo"],
					$proc["rowThree"],
					$proc["number"],
					$proc["colOne"],
					$proc["colTwo"],
					$proc["colThree"]
				);
				break;
			case ThreeColOneNumberInThreeRow:
				printf(
					"column: %d %d %d, value: %d, row: %d %d %d\n",
					$proc["colOne"],
					$proc["colTwo"],
					$proc["colThree"],
					$proc["number"],
					$proc["rowOne"],
					$proc["rowTwo"],
					$proc["rowThree"]
				);
				break;
			default:
				printf("Do Not To Here: Default\n");
				break;
		}
	};
}
