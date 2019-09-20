local sudoku = require("libluasudoku")

return {
	New = function(rows, cols, maxNodes)
		local matrix = {
			handler = sudoku.CreateBoolMatrix(rows, cols, maxNodes)
		}
		setmetatable(matrix, {
			__index = {
				SetMatrixRowData = function(matrix, row)
					-- here can be optimized
					sudoku.SetMatrixRowData(matrix.handler, row)
				end,
				DancingLinks = function(matrix, justOne, callback)
					return sudoku.DancingLinks(matrix.handler, justOne, callback)
				end
			},
			__gc = function(matrix)
				sudoku.DestroyBoolMatrix(matrix.handler)
			end
		})
		return matrix
	end
}
