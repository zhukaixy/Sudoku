package sudoku

/*
#cgo CFLAGS: -I../../../include
#cgo LDFLAGS: -L../../../buildXcode/sudoku/Debug -lsudoku

#include <string.h>
#include "sudoku.h"

int readSudokuData(void* data, int row, int col);
void writeSudokuData(void* data, int row, int col, int value, int type);
void processCallback(void* data, SolveProcedure* proc);
void answerSudokuCallback(void* data, char* ans);
*/
import "C"
import (
	"reflect"
	"unsafe"
)

// 9*9*2:num+' ', 9*2:every line has ' '*2, 9:every line has '\n', 2*'\n'+'\0'
const RESULT_BUFFER_SIZE int = (9*9*2 + 9*2 + 9 + 2 + 1)
const BOARD_SIZE int = (9 * 9)

const (
	None = iota
	GridOnlyOnePosibility
	RowNumberOnlyOneGrid
	ColNumberOnlyOneGrid
	BlockNumberOnlyOneGrid
) // SolveType
const (
	DoNotImprove = iota

	Row2GridWith2Posibility
	Col2GridWith2Posibility
	Block2GridWith2Posibility

	Row3GridWith3Posibility
	Col3GridWith3Posibility
	Block3GridWith3Posibility

	Row2NumberIn2Grid
	Col2NumberIn2Grid
	Block2NumberIn2Grid

	Row3NumberIn3Grid
	Col3NumberIn3Grid
	Block3NumberIn3Grid

	InBlockNumberInOneRow
	InBlockNumberInOneCol

	InRowNumberInBlock
	InColNumberInBlock

	TwoRowOneNumberInTwoCol
	TwoColOneNumberInTwoRow

	ThreeRowOneNumberInThreeCol
	ThreeColOneNumberInThreeRow
) // ImproveType
type SolveProcedure struct {
	improveType int32
	gridOneX    int32 // [1, 9]
	gridOneY    int32
	gridTwoX    int32
	gridTwoY    int32
	gridThreeX  int32
	gridThreeY  int32
	numberOne   int32 // [1, 9]
	numberTwo   int32
	numberThree int32
	panelRow    int32 // [1, 3]
	panelCol    int32
	number      int32 // [1, 9]
	line        int32 // [1, 9]
	rowOne      int32 // [1, 9]
	rowTwo      int32
	rowThree    int32
	colOne      int32
	colTwo      int32
	colThree    int32
}

// row and col are in the range of 1-9
type SudokuReadData func(row int32, col int32) int32

// row col and value are in the range of 1-9
type SudokuWriteData func(row int32, col int32, value int32, improveType int32)
type SolveProcessCallback func(proc *SolveProcedure)

// ans is a null terminate char array
type SudokuAnswerCallback func(ans string)

type Sudoku struct {
	sudo         *C.Sudoku
	ReadFunc     SudokuReadData
	WriteFunc    SudokuWriteData
	ProcCallback SolveProcessCallback
	AnswerCB     SudokuAnswerCallback
}

//export readSudokuData
func readSudokuData(data unsafe.Pointer, row C.int, col C.int) C.int {
	sudoku := (*Sudoku)(unsafe.Pointer(data))
	return C.int(sudoku.ReadFunc(int32(row), int32(col)))
}

//export writeSudokuData
func writeSudokuData(data unsafe.Pointer, row C.int, col C.int, value C.int, improveType C.int) {
	sudoku := (*Sudoku)(unsafe.Pointer(data))
	sudoku.WriteFunc(int32(row), int32(col), int32(value), int32(improveType))
}

//export processCallback
func processCallback(data unsafe.Pointer, proc *C.SolveProcedure) {
	sudoku := (*Sudoku)(unsafe.Pointer(data))
	if sudoku.ProcCallback == nil {
		return
	}
	sudoku.ProcCallback((*SolveProcedure)(unsafe.Pointer(proc)))
}

//export answerSudokuCallback
func answerSudokuCallback(data unsafe.Pointer, ans *C.char) {
	sudoku := (*Sudoku)(unsafe.Pointer(data))
	if sudoku.AnswerCB == nil {
		return
	}
	var answer string
	var handler = (*reflect.StringHeader)(unsafe.Pointer(&answer))
	handler.Data = uintptr(unsafe.Pointer(ans))
	handler.Len = int(C.strlen(ans))
	sudoku.AnswerCB(answer)
}

func (sudoku *Sudoku) CreateSudoku(readFunc SudokuReadData, writeFunc SudokuWriteData, procCallback SolveProcessCallback) {
	sudoku.ReadFunc = readFunc
	sudoku.WriteFunc = writeFunc
	sudoku.ProcCallback = procCallback
	tmpRead := (C.SudokuReadData)(C.readSudokuData)
	tmpWrite := (C.SudokuWriteData)(C.writeSudokuData)
	tmpProc := (C.SolveProcessCallback)(C.processCallback)
	// here should be unsafe.Pointer(&sudoku.sudo), not unsafe.Pointer(sudoku), I don't know why
	sudoku.sudo = C.CreateSudoku(tmpRead, tmpWrite, tmpProc, unsafe.Pointer(&sudoku.sudo))
}

func (sudoku *Sudoku) DestroySudoku() {
	if sudoku.sudo == nil {
		return
	}
	C.DestroySudoku(sudoku.sudo)
}

func VerifySudokuBoard(board []int32) bool {
	return bool(C.VerifySudokuBoard((*C.int)(unsafe.Pointer(&board[0]))))
}
func (sudoku *Sudoku) VerifySudoku() bool {
	return bool(C.VerifySudoku(sudoku.sudo))
}
func (sudoku *Sudoku) GetKnownCount() int32 {
	return int32(C.GetKnownCount(sudoku.sudo))
}
func (sudoku *Sudoku) MakeResultString() string {
	buffer := make([]byte, RESULT_BUFFER_SIZE)
	var result string
	var handler = (*reflect.StringHeader)(unsafe.Pointer(&result))
	handler.Data = uintptr(unsafe.Pointer(&buffer))
	handler.Len = int(RESULT_BUFFER_SIZE)
	C.MakeResultString(sudoku.sudo, (*C.char)(unsafe.Pointer(&buffer)), C.int(RESULT_BUFFER_SIZE))
	return result
}
func (sudoku *Sudoku) CalculateSudokuAll(dancing bool, cb SudokuAnswerCallback) int32 {
	sudoku.AnswerCB = cb
	ansCB := (C.SudokuAnswerCallback)(C.answerSudokuCallback)
	// here should be unsafe.Pointer(&sudoku.sudo), not unsafe.Pointer(sudoku), I don't know why
	return int32(C.CalculateSudokuAll(sudoku.sudo, C.bool(dancing), ansCB, unsafe.Pointer(&sudoku.sudo)))
}
func SolveTypeName(solveType int32) string {
	pName := C.SolveTypeName((C.SolveType)(solveType))
	var name string
	var handler = (*reflect.StringHeader)(unsafe.Pointer(&name))
	handler.Data = uintptr(unsafe.Pointer(pName))
	handler.Len = int(C.strlen(pName))
	return name
}
func ImproveTypeName(improveType int32) string {
	pName := C.ImproveTypeName((C.ImproveType)(improveType))
	var name string
	var handler = (*reflect.StringHeader)(unsafe.Pointer(&name))
	handler.Data = uintptr(unsafe.Pointer(pName))
	handler.Len = int(C.strlen(pName))
	return name
}
