package sudoku

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
