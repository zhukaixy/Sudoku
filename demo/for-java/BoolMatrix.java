public class BoolMatrix {
	long matrixHandler;
	public BoolMatrix(int rows, int cols, int maxNodes) {
		matrixHandler = SudokuLib.CreateBoolMatrix(rows, cols, maxNodes);
	}
	public void finalize()
	{
		SudokuLib.DestroyBoolMatrix(matrixHandler);
	}
	public void SetMatrixRowData(int[] data) {
		SudokuLib.SetMatrixRowData(matrixHandler, data);
	}
	public int DancingLinks(boolean justOne, IMatrixCallback cb) {
		return SudokuLib.DancingLinks(matrixHandler, justOne?1:0, cb);
	}
}
