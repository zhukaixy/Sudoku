local DoNotImprove = function(proc)
	return "Do Not Improve"
end
local GridWithPosibility2 = function(proc)
	return string.format("gridOne: %d %d, gridTwo: %d %d, value: %d %d",
		proc.gridOneX,
		proc.gridOneY,
		proc.gridTwoX,
		proc.gridTwoY,
		proc.numberOne,
		proc.numberTwo)
end
local GridWithPosibility3 = function(proc)
	return string.format("gridOne: %d %d, gridTwo: %d %d, gridThree: %d %d, value: %d %d %d",
		proc.gridOneX,
		proc.gridOneY,
		proc.gridTwoX,
		proc.gridTwoY,
		proc.gridThreeX,
		proc.gridThreeY,
		proc.numberOne,
		proc.numberTwo,
		proc.numberThree)
end
local NumberInGrid2 = function(proc)
	return string.format("value: %d %d, gridOne: %d %d, gridTwo: %d %d",
	proc.numberOne,
	proc.numberTwo,
	proc.gridOneX,
	proc.gridOneY,
	proc.gridTwoX,
	proc.gridTwoY)
end
local NumberInGrid3 = function(proc)
	return string.format("value: %d %d %d, gridOne: %d %d, gridTwo: %d %d, gridThree: %d %d",
	proc.numberOne,
	proc.numberThree,
	proc.numberTwo,
	proc.gridOneX,
	proc.gridOneY,
	proc.gridTwoX,
	proc.gridTwoY,
	proc.gridThreeX,
	proc.gridThreeY)
end
local BlockNumberInRowCol = function(proc)
	return string.format("block: %d %d, value: %d, line: %d", proc.panelRow, proc.panelCol, proc.number, proc.line)
end
local RowColNumberInBlock = function(proc)
	return string.format("line: %d, value: %d, block: %d %d", proc.line, proc.number, proc.panelRow, proc.panelCol)
end
local TwoRowOneNumberInTwoCol = function(proc)
	return string.format("row: %d %d, value: %d, column: %d %d",
	proc.rowOne,
	proc.rowTwo,
	proc.number,
	proc.colOne,
	proc.colTwo)
end
local TwoColOneNumberInTwoRow = function(proc)
	return string.format("column: %d %d, value: %d, row: %d %d",
	proc.colOne,
	proc.colTwo,
	proc.number,
	proc.rowOne,
	proc.rowTwo)
end
local ThreeRowOneNumberInThreeCol = function(proc)
	return string.format("row: %d %d %d, value: %d, column: %d %d %d",
	proc.rowOne,
	proc.rowTwo,
	proc.rowThree,
	proc.number,
	proc.colOne,
	proc.colTwo,
	proc.colThree)
end
local ThreeColOneNumberInThreeRow = function(proc)
	return string.format("column: %d %d %d, value: %d, row: %d %d %d",
	proc.colOne,
	proc.colTwo,
	proc.colThree,
	proc.number,
	proc.rowOne,
	proc.rowTwo,
	proc.rowThree)
end
local AllImproveFunctions = {
	GridWithPosibility2,
	GridWithPosibility2,
	GridWithPosibility2,
	GridWithPosibility3,
	GridWithPosibility3,
	GridWithPosibility3,
	NumberInGrid2,
	NumberInGrid2,
	NumberInGrid2,
	NumberInGrid3,
	NumberInGrid3,
	NumberInGrid3,
	BlockNumberInRowCol,
	BlockNumberInRowCol,
	RowColNumberInBlock,
	RowColNumberInBlock,
	TwoRowOneNumberInTwoCol,
	TwoColOneNumberInTwoRow,
	ThreeRowOneNumberInThreeCol,
	ThreeColOneNumberInThreeRow,
	[0] = DoNotImprove
}

return {
	AllImproveFunctions = AllImproveFunctions
}
