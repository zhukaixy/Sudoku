using System;
using System.Runtime.InteropServices;

namespace ForCS
{
	public enum SolveType
	{
		None = 0,
		GridOnlyOnePosibility,
		RowNumberOnlyOneGrid,
		ColNumberOnlyOneGrid,
		BlockNumberOnlyOneGrid
	};
	public enum ImproveType
	{
		DoNotImprove = 0,

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
	};
	public struct SolveProcedure
	{
		public int type; // typeof type is ImproveType
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
	};
	public class SudokuLib
	{
		const string SUDOKU_LIB = "sudoku";
		// 9*9*2:num+' ', 9*2:every line has ' '*2, 9:every line has '\n', 2*'\n'+'\0'
		public const int RESULT_BUFFER_SIZE = (9 * 9 * 2 + 9 * 2 + 9 + 2 + 1);
		public const int BOARD_SIZE = (9 * 9);

		#region BoolMatrix API
		// answer is an array with row number in [0, rows-1]
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
		// row and col are in the range of 1-9
		public delegate int SudokuReadData(IntPtr data, int row, int col);
		// row col and value are in the range of 1-9, typeof type is SolveType
		public delegate void SudokuWriteData(IntPtr data, int row, int col, int value, int type);
		// typeof proc is SolveProcedure*
		public delegate void SolveProcessCallback(IntPtr data, IntPtr proc);
		// ans is a null terminate char array
		public delegate void SudokuAnswerCallback(IntPtr data, IntPtr ans);
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
