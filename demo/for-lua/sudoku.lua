local cmod = require("libluasudoku")

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
	New = function(readFunc, writeFunc, procCallback)
		local sudoku = {
			handler = cmod.CreateSudoku(readFunc, writeFunc, procCallback)
		}
		setmetatable(matrix, {
			__index = {
				VerifySudoku = function(sudoku)
					return cmod.VerifySudoku(sudoku.handler)
				end,
				GetKnownCount = function(sudoku)
					return cmod.GetKnownCount(sudoku.handler)
				end,
				MakeResultString = function(sudoku)
					return cmod.MakeResultString(sudoku.handler)
				end,
				CalculateSudokuAll = function(sudoku, dancing, callback)
					return cmod.DancingLinks(sudoku.handler, dancing, callback)
				end
			},
			__gc = function(sudoku)
				cmod.DestroySudoku(sudoku.handler)
			end
		})
		return matrix
	end,
	VerifySudokuBoard = function(board)
		return cmod.VerifySudokuBoard(board)
	end,
	SolveTypeName = function(type)
		return cmod.SolveTypeName(type)
	end,
	ImproveTypeName = function(type)
		return cmod.ImproveTypeName(type)
	end,
	SolveType = CreatEnumTable(SolveTypeEnum),
	ImproveType = CreatEnumTable(ImproveTypeEnum) 
}
