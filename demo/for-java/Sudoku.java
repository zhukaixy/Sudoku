public class Sudoku {
	long sudoHandler;
	public Sudoku(ISudokuCallback cb) {
		sudoHandler = SudokuLib.CreateSudoku(cb);
	}
	public void finalize() {
		SudokuLib.DestroySudoku(sudoHandler);
	}
	public static boolean VerifySudokuBoard(int[] board) {
		return SudokuLib.VerifySudokuBoard(board) != 0;
	}
	public boolean VerifySudoku() {
		return SudokuLib.VerifySudoku(sudoHandler) != 0;
	}
	public int GetKnownCount() {
		return SudokuLib.GetKnownCount(sudoHandler);
	}
	public String MakeResultString() {
		return SudokuLib.MakeResultString(sudoHandler);
	}
	public int CalculateSudokuAll(boolean dancing, ISudokuAnswerCallback cb) {
		return SudokuLib.CalculateSudokuAll(sudoHandler, dancing?1:0, cb);
	}
	public static String SolveTypeName(SolveType type) {
		return SudokuLib.SolveTypeName(type.ordinal());
	}
	public static String ImproveTypeName(ImproveType type) {
		return SudokuLib.ImproveTypeName(type.ordinal());
	}
}
