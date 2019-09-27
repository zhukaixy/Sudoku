using System;
using System.Runtime.InteropServices;

namespace ForCS
{
	// row and col are in the range of 1-9
	public delegate int SudokuReadData(int row, int col);
	// row col and value are in the range of 1-9, typeof type is SolveType
	public delegate void SudokuWriteData(int row, int col, int value, SolveType type);
	// typeof proc is SolveProcedure*
	public delegate void SolveProcessCallback(SolveProcedure proc);
	// ans is a null terminate char array
	public delegate void SudokuAnswerCallback(string ans);
	public class Sudoku
	{
		private IntPtr sudo;
		public Sudoku(SudokuReadData readFunc, SudokuWriteData writeFunc, SolveProcessCallback procCallback)
		{
			if (readFunc == null || writeFunc == null)
			{
				throw new Exception("read function and write function should not be null!");
			}
			IntPtr readPtr = Marshal.GetFunctionPointerForDelegate(new SudokuLib.SudokuReadData((IntPtr data, int row, int col) =>
			{
				return readFunc.Invoke(row, col);
			}));
			IntPtr writePtr = Marshal.GetFunctionPointerForDelegate(new SudokuLib.SudokuWriteData((IntPtr data, int row, int col, int value, int type) =>
			{
				writeFunc.Invoke(row, col, value, (SolveType)type);
			}));
			IntPtr solvePtr = Marshal.GetFunctionPointerForDelegate(new SudokuLib.SolveProcessCallback((IntPtr data, IntPtr proc) =>
			{
				if (procCallback == null)
				{
					return;
				}
				SolveProcedure procedure = (SolveProcedure)Marshal.PtrToStructure(proc, typeof(SolveProcedure));
				procCallback.Invoke(procedure);
			}));
			sudo = SudokuLib.CreateSudoku(readPtr, writePtr, solvePtr, IntPtr.Zero);
		}
		~Sudoku()
		{
			SudokuLib.DestroySudoku(sudo);
		}
		public bool VerifySudoku()
		{
			return SudokuLib.VerifySudoku(sudo) > 0;
		}
		public int GetKnownCount()
		{
			return SudokuLib.GetKnownCount(sudo);
		}
		public string MakeResultString()
		{
			IntPtr pData = Marshal.AllocHGlobal(SudokuLib.RESULT_BUFFER_SIZE);
			SudokuLib.MakeResultString(sudo, pData, SudokuLib.RESULT_BUFFER_SIZE);
			string result = Marshal.PtrToStringAnsi(pData, SudokuLib.RESULT_BUFFER_SIZE);
			Marshal.FreeHGlobal(pData);
			return result;
		}
		public int CalculateSudokuAll(bool dancing, SudokuAnswerCallback cb)
		{
			IntPtr ansPtr = Marshal.GetFunctionPointerForDelegate(new SudokuLib.AnswerCallback((IntPtr data, IntPtr answer, int size) =>
			{
				if (cb == null)
				{
					return;
				}
				string result = Marshal.PtrToStringAnsi(answer, size);
				cb.Invoke(result);
			}));
			return SudokuLib.CalculateSudokuAll(sudo, (byte)(dancing ? 1 : 0), ansPtr, IntPtr.Zero);
		}

		public static bool VerifySudokuBoard(int[] board)
		{
			if (board.Length < SudokuLib.BOARD_SIZE)
			{
				return false;
			}
			IntPtr pData = Marshal.AllocHGlobal(sizeof(int) * board.Length);
			Marshal.Copy(board, 0, pData, board.Length);
			int ret = (int)SudokuLib.VerifySudokuBoard(pData);
			Marshal.FreeHGlobal(pData);
			return ret > 0;
		}
		public static string SolveTypeName(SolveType type)
		{
			IntPtr name = SudokuLib.SolveTypeName((int)type);
			return Marshal.PtrToStringAnsi(name);
		}
		public static string ImproveTypeName(ImproveType type)
		{
			IntPtr name = SudokuLib.ImproveTypeName((int)type);
			return Marshal.PtrToStringAnsi(name);
		}
	}
}
