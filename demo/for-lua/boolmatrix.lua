local cmod = require("libluasudoku")

return {
	New = function(rows, cols, maxNodes)
		local matrix = {
			handler = cmod.CreateBoolMatrix(rows, cols, maxNodes)
		}
		setmetatable(matrix, {
			__index = {
				SetMatrixRowData = function(matrix, row)
					-- here can be optimized
					cmod.SetMatrixRowData(matrix.handler, row)
				end,
				DancingLinks = function(matrix, justOne, callback)
					return cmod.DancingLinks(matrix.handler, justOne, callback)
				end
			},
			__gc = function(matrix)
				cmod.DestroyBoolMatrix(matrix.handler)
			end
		})
		return matrix
	end
}
