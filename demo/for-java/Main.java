class MatrixCB implements IMatrixCallback {
	public void AnswerCallback(int[] answer) {
		System.out.print("BoolMatrixAnswer:");
		for (int i = 0; i < answer.length; i++) {
			int tmp = answer[i] + 1;
			System.out.print("" + tmp + " ");
		}
		System.out.print("\n");
	}
}

public class Main {
	public static void main(String[] args) {
		BoolMatrixUsage();
	}
	static void BoolMatrixUsage() {
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
		int count = matrix.DancingLinks(false, new MatrixCB());
		System.out.println("BoolMatrix Answer Count: " + count);
	}
}
