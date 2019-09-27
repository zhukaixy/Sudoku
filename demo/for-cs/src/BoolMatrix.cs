using System;
using System.Runtime.InteropServices;

namespace ForCS
{
	public delegate void AnswerCallback(int[] answer);
	public class BoolMatrix
	{
		private IntPtr matrix;
		private AnswerCallback ansCallback;
		public BoolMatrix(int rows, int cols, int maxNodes)
		{
			matrix = SudokuLib.CreateBoolMatrix(rows, cols, maxNodes);
		}
		~BoolMatrix()
		{
			SudokuLib.DestroyBoolMatrix(matrix);
		}
		public void SetMatrixRowData(int[] data)
		{
			IntPtr pData = Marshal.AllocHGlobal(sizeof(int) * data.Length);
			Marshal.Copy(data, 0, pData, data.Length);
			SudokuLib.SetMatrixRowData(matrix, pData, data.Length);
			Marshal.FreeHGlobal(pData);
		}
		private void DancingCallback(IntPtr data, IntPtr answer, int size)
		{
			int[] ansArray = new int[size];
			Marshal.Copy(answer, ansArray, 0, size);
			ansCallback.Invoke(ansArray);
		}
		public int DancingLinks(bool justOne, AnswerCallback cb)
		{
			ansCallback = cb;
			IntPtr callback = Marshal.GetFunctionPointerForDelegate(new SudokuLib.AnswerCallback(DancingCallback));
			return SudokuLib.DancingLinks(matrix, (byte)(justOne ? 1 : 0), callback, IntPtr.Zero);
		}
	}
}
