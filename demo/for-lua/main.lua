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
	for i, v in ipairs(answer) do answer[i] = v + 1 end
	print("BoolMatrixAnswer: " .. table.concat(answer, " "))
end)
print("BoolMatrix Answer Count: " .. count)
matrix = nil
collectgarbage()
collectgarbage()


local Usage = function(exec)
	print(string.format("Usage: %s <file>", exec));
	print("\t<file>: The sudoku file path");
	print(string.format("\tor using %s with stdin", exec));
end

local GetSudokuFromFile = function(file, board)
	local BOARD_SIZE = 9 * 9
	local count = 1
	while count <= BOARD_SIZE do
		local c = file:read(1)
		if c == nil then return false end
		if c >= '0' and c <= '9' then
			board[count] = tonumber(c)
			count = count + 1
		end
	end
	return true
end

local DisplaySudoku = function(board)
	local buffer = {}
	for i = 0, 8 do
		for j = 0, 8 do
			local index = i*9+j;
			table.insert(buffer, board[index+1])
			table.insert(buffer, " ")
			if j == 2 or j == 5 then
				table.insert(buffer, " ")
			end
		end
		table.insert(buffer, "\n")
		if i == 2 or i == 5 then
			table.insert(buffer, "\n")
		end
	end
	print(table.concat(buffer))
end

-- Main Function Start

local argv = {...}
local argc = #argv
if argc ~= 0 and argc ~= 1 then 
	Usage("lua main.lua")
	os.exit(-1)
end

local file = io.stdin
if argc == 1 then file = io.open(argv[1]) end
local board = {}
GetSudokuFromFile(file, board)
file:close()
file = nil
local board_dancing = {}
for i = 1, 81 do board_dancing[i] = board[i] end

local sudoku = require("sudoku")

do
	local sudo = sudoku.New(function(row, col)
		local index = (row - 1) * 9 + col - 1
		return board[index+1]
	end, function(row, col, value, type)
		local index = (row - 1) * 9 + col - 1
		board[index+1] = value
		print(string.format("Solve: %s row:%d column:%d value:%d", sudoku.SolveTypeName(type), row, col, value))
	end, function(proc)
		local solveproc = require("solveproc")
		local buffer = {}
		table.insert(buffer, string.format("Improve: %s ", sudoku.ImproveTypeName(proc.type)));
		table.insert(buffer, solveproc.AllImproveFunctions[proc.type](proc))
		print(table.concat(buffer))
	end)
	local cnt = sudo:GetKnownCount();
	print(string.format("Sudoku Known Count: %d", cnt));
	print("Calculate step by step");
	local num = sudo:CalculateSudokuAll(false);
	print(string.format("Answer Count: %d", num));
	DisplaySudoku(board);
	local status = sudoku.VerifySudokuBoard(board);
	local statusStr = "False"
	if status then statusStr = "True" end
	print(string.format("Verify: %s", statusStr));
	sudo = nil
	collectgarbage()
	collectgarbage()
end

do
	local sudo = sudoku.New(function(row, col)
		local index = (row - 1) * 9 + col - 1
		return board_dancing[index + 1]
	end, function(row, col, value, type)
		local index = (row - 1) * 9 + col - 1
		board_dancing[index + 1] = value
	end)
	print("Calculate using dancing");
	local num = sudo:CalculateSudokuAll(true)
	print(string.format("Answer Count: %d", num));
	print("One of it:");
	DisplaySudoku(board_dancing);
	local status = sudoku.VerifySudokuBoard(board);
	local statusStr = "False"
	if status then statusStr = "True" end
	print(string.format("Verify: %s", statusStr));
	sudo = nil
	collectgarbage()
	collectgarbage()
end
