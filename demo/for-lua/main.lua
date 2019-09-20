local row1 = {0, 3, 6}
local row2 = {0, 3}
local row3 = {3, 4, 6}
local row4 = {2, 4, 5}
local row5 = {1, 2, 5, 6}
local row6 = {1, 6}

local matrix = require("boolmatrix").New(6, 7, 17)
matrix:SetMatrixRowData(row1)
matrix:SetMatrixRowData(row2)
matrix:SetMatrixRowData(row3)
matrix:SetMatrixRowData(row4)
matrix:SetMatrixRowData(row5)
matrix:SetMatrixRowData(row6)
local count = matrix:DancingLinks(false, function(answer)
	for k, v in ipairs(answer) do answer[k] = tostring(v) .. " " end
	print("BoolMatrixAnswer: " .. table.concat(answer))
end)
print("BoolMatrix Answer Count: " .. count)
matrix = nil
collectgarbage()
collectgarbage()
