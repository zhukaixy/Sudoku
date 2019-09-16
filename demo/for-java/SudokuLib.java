interface IMatrixCallback {
	void AnswerCallback(int[] data);
}
// interface SudokuCallback {

// }
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
}
