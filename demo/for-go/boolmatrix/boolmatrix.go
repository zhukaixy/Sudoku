package boolmatrix

/*
#include <bool-matrix.h>

void CgoAnswerCB(void* data, int* answer, int size);
*/
import "C"
import (
	"reflect"
	"unsafe"
)

//export CgoAnswerCB
func CgoAnswerCB(data unsafe.Pointer, answer *C.int, size C.int) {
	var ans []int32
	var ansHandler = (*reflect.SliceHeader)(unsafe.Pointer(&ans))
	ansHandler.Data = uintptr(unsafe.Pointer(answer))
	ansHandler.Len = int(size)
	ansHandler.Cap = int(size)
	boolMatrix := (*BoolMatrix)(unsafe.Pointer(data))
	// ans := []int((unsafe.Pointer(answer))[:size:size])
	boolMatrix.AnswerCB(ans)
}

type AnswerCallback func(answer []int32)

type BoolMatrix struct {
	matrix   *C.BoolMatrix
	AnswerCB AnswerCallback
}

// rows is the number of matrix row
// cols is the number of matrix column
// maxNodes is the number of 1 in the matrix
func (boolMatrix *BoolMatrix) CreateBoolMatrix(rows, cols, maxNodes int) {
	boolMatrix.matrix = C.CreateBoolMatrix(C.int(rows), C.int(cols), C.int(maxNodes))
}

func (boolMatrix *BoolMatrix) DestroyBoolMatrix() {
	if boolMatrix.matrix == nil {
		return
	}
	C.DestroyBoolMatrix(boolMatrix.matrix)
	boolMatrix.matrix = nil
}

// data is an array with one position in that row, position are in the range of [0, cols-1]
func (boolMatrix *BoolMatrix) SetMatrixRowData(data []int32) {
	if boolMatrix.matrix == nil {
		return
	}
	C.SetMatrixRowData(boolMatrix.matrix, (*C.int)(unsafe.Pointer(&data[0])), C.int(len(data)))
}

// return the number of this call has calculated(the result)
func (boolMatrix *BoolMatrix) DancingLinks(justOne bool, cb AnswerCallback) int {
	if boolMatrix.matrix == nil {
		return 0
	}
	boolMatrix.AnswerCB = cb
	ansCB := (C.AnswerCallback)(C.CgoAnswerCB)
	// here can be unsafe.Pointer(boolMatrix), no need unsafe.Pointer(&boolMatrix.matrix), I don't know why
	return int(C.DancingLinks(boolMatrix.matrix, C.bool(justOne), ansCB, unsafe.Pointer(boolMatrix)))
}
