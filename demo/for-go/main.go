package main

import (
	"fmt"
	"for-go/boolmatrix"
	"for-go/sudoku"
	"os"
)

func main() {
	boolMatrixUsage()
	argv := os.Args
	argc := len(argv)
	if argc != 1 && argc != 2 {
		usage(argv[0])
		os.Exit(-1)
	}
	file := os.Stdin
	if argc == 2 {
		var err error // here must declare first, if use := , file will be redefine
		file, err = os.OpenFile(argv[1], os.O_RDONLY, 0)
		if err != nil {
			fmt.Println(err)
			usage(argv[0])
			os.Exit(-1)
		}
	}
	board := getSudokuFromFile(file)
	board_dancing := new([sudoku.BOARD_SIZE]int32)
	for index := 0; index < sudoku.BOARD_SIZE; index++ {
		board_dancing[index] = board[index]
	}

	{
		sudo := new(sudoku.Sudoku)
		sudo.CreateSudoku(func(row int32, col int32) int32 {
			index := (row-1)*9 + (col - 1)
			return board[index]
		}, func(row int32, col int32, value int32, improveType int32) {
			index := (row-1)*9 + (col - 1)
			board[index] = value
		}, nil)
		count := sudo.GetKnownCount()
		fmt.Printf("Sudoku Known Count: %d\n", count)
		fmt.Printf("Calculate step by step\n")
		num := sudo.CalculateSudokuAll(false, nil)
		fmt.Printf("Answer Count: %d\n", num)
		displaySudoku(board)
		status := sudoku.VerifySudokuBoard(board)
		statusStr := ""
		if status {
			statusStr = "True"
		} else {
			statusStr = "False"
		}
		fmt.Printf("Verify: %s\n", statusStr)
		sudo.DestroySudoku()
	}
	fmt.Println("")
	{
		sudo := new(sudoku.Sudoku)
		sudo.CreateSudoku(func(row int32, col int32) int32 {
			index := (row-1)*9 + (col - 1)
			return board_dancing[index]
		}, func(row int32, col int32, value int32, improveType int32) {
			index := (row-1)*9 + (col - 1)
			board_dancing[index] = value
		}, nil)
		fmt.Printf("Calculate using dancing\n")
		num := sudo.CalculateSudokuAll(true, nil)
		fmt.Printf("Answer Count: %d\n", num)
		fmt.Printf("One of it:\n")
		displaySudoku(board)
		status := sudoku.VerifySudokuBoard(board)
		statusStr := ""
		if status {
			statusStr = "True"
		} else {
			statusStr = "False"
		}
		fmt.Printf("Verify: %s\n", statusStr)
		sudo.DestroySudoku()
	}
}

func boolMatrixUsage() {
	row1 := []int32{0, 3, 6}
	row2 := []int32{0, 3}
	row3 := []int32{3, 4, 6}
	row4 := []int32{2, 4, 5}
	row5 := []int32{1, 2, 5, 6}
	row6 := []int32{1, 6}

	matrix := new(boolmatrix.BoolMatrix)
	matrix.CreateBoolMatrix(6, 7, 17)
	matrix.SetMatrixRowData(row1)
	matrix.SetMatrixRowData(row2)
	matrix.SetMatrixRowData(row3)
	matrix.SetMatrixRowData(row4)
	matrix.SetMatrixRowData(row5)
	matrix.SetMatrixRowData(row6)
	count := matrix.DancingLinks(false, func(answer []int32) {
		for index := 0; index < len(answer); index++ {
			answer[index]++
		}
		fmt.Println("BoolMatrixAnswer:", answer)
	})
	fmt.Println("BoolMatrix Answer Count:", count)
	matrix.DestroyBoolMatrix()
}

func usage(exec string) {
	fmt.Printf("Usage: %s <file>\n", exec)
	fmt.Printf("\t<file>: The sudoku file path\n")
	fmt.Printf("\tor using %s with stdin\n", exec)
}

func getSudokuFromFile(file *os.File) []int32 {
	board := make([]int32, sudoku.BOARD_SIZE)
	buffer := make([]byte, 1)

	count := 0
	for count < sudoku.BOARD_SIZE {
		cnt, err := file.Read(buffer)
		if err != nil || cnt == 0 {
			return nil
		}
		if buffer[0] >= '0' && buffer[0] <= '9' {
			board[count] = int32(buffer[0] - '0')
			count++
		}
	}
	return board
}

func displaySudoku(board []int32) {
	if len(board) < sudoku.BOARD_SIZE {
		return
	}
	for i := 0; i < 9; i++ {
		for j := 0; j < 9; j++ {
			index := i*9 + j
			fmt.Printf("%d ", board[index])
			if j == 2 || j == 5 {
				fmt.Printf(" ")
			}
		}
		fmt.Printf("\n")
		if i == 2 || i == 5 {
			fmt.Printf("\n")
		}
	}
}
