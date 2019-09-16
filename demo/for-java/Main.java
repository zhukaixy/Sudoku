public class Main implements IMatrixCallback, ISudokuCallback, ISudokuAnswerCallback {
	public static void main(String[] args) {
		Main self = new Main();
		self.BoolMatrixUsage();
		int argc = args.length;
		if (argc != 0 && argc != 1) {
			Usage("java Main");
			System.exit(-1);
		}

	}
	public void AnswerCallback(int[] answer) {
		System.out.print("BoolMatrixAnswer:");
		for (int i = 0; i < answer.length; i++) {
			int tmp = answer[i] + 1;
			System.out.printf("%d ", tmp);
		}
		System.out.print("\n");
	}
	void BoolMatrixUsage() {
		int[] row1 = { 0, 3, 6 };
		int[] row2 = { 0, 3 };
		int[] row3 = { 3, 4, 6 };
		int[] row4 = { 2, 4, 5 };
		int[] row5 = { 1, 2, 5, 6 };
		int[] row6 = { 1, 6 };
		BoolMatrix matrix = new BoolMatrix(6, 7, 17);
		matrix.SetMatrixRowData(row1);
		matrix.SetMatrixRowData(row2);
		matrix.SetMatrixRowData(row3);
		matrix.SetMatrixRowData(row4);
		matrix.SetMatrixRowData(row5);
		matrix.SetMatrixRowData(row6);
		int count = matrix.DancingLinks(false, this);
		System.out.printf("BoolMatrix Answer Count: %d\n", count);
	}
	static void Usage(String exec) {
		System.out.printf("Usage: %s <file>\n", exec);
		System.out.printf("\t<file>: The sudoku file path\n");
		System.out.printf("\tor using %s with stdin\n", exec);
	}
	// row and col are in the range of 1-9
	public int SudokuReadData(int row, int col) {
		return 0;
	}
	// row col and value are in the range of 1-9
	public void SudokuWriteData(int row, int col, int value, int type) {

	}
	public void SolveProcessCallback(SolveProcedure proc) {

	}
	// ans is a null terminate char array
	public void SudokuAnswerCallback(int[] ans) {
		
	}
}
