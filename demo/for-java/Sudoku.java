public class Sudoku {
	long sudoHandler;
	public Sudoku(ISudokuCallback cb) {
		sudoHandler = SudokuLib.CreateSudoku(cb);
	}
	public void finalize() {
		SudokuLib.DestroySudoku(sudoHandler);
	}
	public boolean VerifySudoku() {
		return SudokuLib.VerifySudoku(sudoHandler);
	}
	public int GetKnownCount() {
		return SudokuLib.GetKnownCount(sudoHandler);
	}
	public String MakeResultString() {
		return SudokuLib.MakeResultString(sudoHandler);
	}
	public int CalculateSudokuAll(boolean dancing, ISudokuCallback cb) {
		return SudokuLib.CalculateSudokuAll(sudoHandler, dancing, cb);
	}

	public static boolean VerifySudokuBoard(int[] board) {
		return SudokuLib.VerifySudokuBoard(board);
	}
	public static String SolveTypeName(SolveType type) {
		return SudokuLib.SolveTypeName(type.ordinal());
	}
	public static String ImproveTypeName(ImproveType type) {
		return SudokuLib.ImproveTypeName(type.ordinal());
	}
}
