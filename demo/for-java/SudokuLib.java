enum SolveType {
	None,
	GridOnlyOnePosibility,
	RowNumberOnlyOneGrid,
	ColNumberOnlyOneGrid,
	BlockNumberOnlyOneGrid
}
enum ImproveType {
	DoNotImprove,

	Row2GridWith2Posibility,
	Col2GridWith2Posibility,
	Block2GridWith2Posibility,

	Row3GridWith3Posibility,
	Col3GridWith3Posibility,
	Block3GridWith3Posibility,

	Row2NumberIn2Grid,
	Col2NumberIn2Grid,
	Block2NumberIn2Grid,

	Row3NumberIn3Grid,
	Col3NumberIn3Grid,
	Block3NumberIn3Grid,

	InBlockNumberInOneRow,
	InBlockNumberInOneCol,

	InRowNumberInBlock,
	InColNumberInBlock,

	TwoRowOneNumberInTwoCol,
	TwoColOneNumberInTwoRow,

	ThreeRowOneNumberInThreeCol,
	ThreeColOneNumberInThreeRow
}
class SolveProcedure {
	public int type;
	public int gridOneX; // [1, 9]
	public int gridOneY;
	public int gridTwoX;
	public int gridTwoY;
	public int gridThreeX;
	public int gridThreeY;
	public int numberOne; // [1, 9]
	public int numberTwo;
	public int numberThree;
	public int panelRow; // [1, 3]
	public int panelCol;
	public int number; // [1, 9]
	public int line; // [1, 9]
	public int rowOne; // [1, 9]
	public int rowTwo;
	public int rowThree;
	public int colOne;
	public int colTwo;
	public int colThree;
}
interface IMatrixCallback {
	void AnswerCallback(int[] data);
}
interface ISudokuCallback {
	// row and col are in the range of 1-9
	int SudokuReadData(int row, int col);
	// row col and value are in the range of 1-9
	void SudokuWriteData(int row, int col, int value, int type);
	void SolveProcessCallback(SolveProcedure proc);
}
interface ISudokuAnswerCallback {
	// ans is a null terminate char array
	void SudokuAnswerCallback(int[] ans);
}
public class SudokuLib {
	static {
		System.loadLibrary("sudokujni");
	}
	// rows is the number of matrix row
	// cols is the number of matrix column
	// maxNodes is the number of 1 in the matrix
	public static native long CreateBoolMatrix(int rows, int cols, int maxNodes);
	public static native void DestroyBoolMatrix(long matrix);
	// data is an array with one position in that row, position are in the range of [0, cols-1]
	public static native void SetMatrixRowData(long matrix, int[] data);
	// return the number of this call has calculated(the result)
	public static native int DancingLinks(long matrix, int justOne, IMatrixCallback cb);

	public static native long CreateSudoku(ISudokuCallback cb);
	public static native void DestroySudoku(long sudo);
	public static native int VerifySudokuBoard(int[] board);
	public static native int VerifySudoku(long sudo);
	public static native int GetKnownCount(long sudo);
	public static native String MakeResultString(long sudo);
	public static native int CalculateSudokuAll(long sudo, int dancing, ISudokuAnswerCallback cb);
	public static native String SolveTypeName(int type);
	public static native String ImproveTypeName(int type);
}
