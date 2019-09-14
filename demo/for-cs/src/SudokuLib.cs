using System;
using System.Runtime.InteropServices;

namespace ForCS
{
	public class SudokuLib
	{
		const string SUDOKU_LIB = "libsudoku";

		#region BoolMatrix API
		public delegate void AnswerCallback(IntPtr data, IntPtr answer, int size);
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr CreateBoolMatrix(int rows, int cols, int maxNodes);
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern void DestroyBoolMatrix(IntPtr matrix);
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern void SetMatrixRowData(IntPtr matrix, IntPtr data, int size);
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern int DancingLinks(IntPtr matrix, int justOne, IntPtr cb, IntPtr data);
		#endregion

		#region Sudoku API
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr CreateSudoku(IntPtr readFunc, IntPtr writeFunc, IntPtr procCallback, IntPtr data);
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern void DestroySudoku(IntPtr sudo);
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern int VerifySudokuBoard(IntPtr board);
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern int VerifySudoku(IntPtr sudo);
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern int GetKnownCount(IntPtr sudo);
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern void MakeResultString(IntPtr sudo, IntPtr buffer, int size);
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern int CalculateSudokuAll(IntPtr sudo, int dancing, IntPtr cb, IntPtr data);
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr SolveTypeName(int type);
		[DllImport(SUDOKU_LIB, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr ImproveTypeName(int type);
		#endregion
	}
}
