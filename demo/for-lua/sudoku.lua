local CreatEnumTable = function(tbl, index) 
	local enumtbl = {} 
	local enumindex = index or 0 
	for i, v in ipairs(tbl) do 
		enumtbl[v] = enumindex + i - 1
	end 
	return enumtbl 
end 
local SolveTypeEnum = {
	"None",
	"GridOnlyOnePosibility",
	"RowNumberOnlyOneGrid",
	"ColNumberOnlyOneGrid",
	"BlockNumberOnlyOneGrid"
}
local ImproveTypeEnum = {
	"DoNotImprove",

	"Row2GridWith2Posibility",
	"Col2GridWith2Posibility",
	"Block2GridWith2Posibility",

	"Row3GridWith3Posibility",
	"Col3GridWith3Posibility",
	"Block3GridWith3Posibility",

	"Row2NumberIn2Grid",
	"Col2NumberIn2Grid",
	"Block2NumberIn2Grid",

	"Row3NumberIn3Grid",
	"Col3NumberIn3Grid",
	"Block3NumberIn3Grid",

	"InBlockNumberInOneRow",
	"InBlockNumberInOneCol",

	"InRowNumberInBlock",
	"InColNumberInBlock",

	"TwoRowOneNumberInTwoCol",
	"TwoColOneNumberInTwoRow",

	"ThreeRowOneNumberInThreeCol",
	"ThreeColOneNumberInThreeRow"
}

return {
	SolveType = CreatEnumTable(SolveTypeEnum),
	ImproveType = CreatEnumTable(ImproveTypeEnum) 
}
