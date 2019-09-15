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
	board_dancing := new([sudoku.BOARD_SIZE]int)
	for index := 0; index < sudoku.BOARD_SIZE; index++ {
		board_dancing[index] = board[index]
	}
	displaySudoku(board)
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

func getSudokuFromFile(file *os.File) []int {
	board := make([]int, sudoku.BOARD_SIZE)
	buffer := make([]byte, 1)

	count := 0
	for count < sudoku.BOARD_SIZE {
		cnt, err := file.Read(buffer)
		if err != nil || cnt == 0 {
			return nil
		}
		if buffer[0] >= '0' && buffer[0] <= '9' {
			board[count] = int(buffer[0] - '0')
			count++
		}
	}
	return board
}

func displaySudoku(board []int) {
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
