using System;
using System.IO;

namespace ForCS
{
	public class SudokuDemo
	{
		static void Main(string[] args)
		{
			BoolMatrixUsage();
			int argc = args.Length;
			if (argc != 0 && argc != 1)
			{
				Usage("mono for-cs.exe");
			}
			StreamReader file;
			if (argc == 1)
			{
				file = new StreamReader(args[0]);
			}
			else
			{
				file = new StreamReader(Console.OpenStandardInput());
			}
			int[] board = GetSudokuFromFile(file);
			file.Close();
			int[] board_dancing = new int[board.Length];
			board.CopyTo(board_dancing, 0);

			{
				Sudoku sudo = new Sudoku((int row, int col) =>
				{
					int index = (row - 1) * 9 + col - 1;
					return board[index];
				}, (int row, int col, int value, SolveType type) =>
				{
					int index = (row - 1) * 9 + col - 1;
					board[index] = value;
					Console.WriteLine("Solve: {0} row:{1} column:{2} value:{3}", Sudoku.SolveTypeName(type), row, col, value);
				}, SolveDisplay);
				int count = sudo.GetKnownCount();
				Console.WriteLine("Sudoku Known Count: {0}", count);
				Console.WriteLine("Calculate step by step");
				int num = sudo.CalculateSudokuAll(false, null);
				Console.WriteLine("Answer Count: {0}", num);
				DisplaySudoku(board);
				bool status = Sudoku.VerifySudokuBoard(board);
				Console.WriteLine("Verify: {0}", status ? "True" : "False");
			}
			Console.WriteLine("");
			{
				Sudoku sudo = new Sudoku((int row, int col) =>
				{
					int index = (row - 1) * 9 + col - 1;
					return board_dancing[index];
				}, (int row, int col, int value, SolveType type) =>
				{
					int index = (row - 1) * 9 + col - 1;
					board_dancing[index] = value;
				}, null);
				Console.WriteLine("Calculate using dancing");
				int num = sudo.CalculateSudokuAll(true, null);
				Console.WriteLine("Answer Count: {0}", num);
				Console.WriteLine("One of it:");
				DisplaySudoku(board_dancing);
				bool status = Sudoku.VerifySudokuBoard(board_dancing);
				Console.WriteLine("Verify: {0}", status ? "True" : "False");
			}
			GC.Collect();
		}
		static void BoolMatrixUsage()
		{
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
			int count = matrix.DancingLinks(false, (int[] answer) =>
			{
				Console.Write("BoolMatrixAnswer: ");
				foreach (int item in answer)
				{
					Console.Write("{0} ", item + 1);
				}
				Console.WriteLine("");
			});
			Console.WriteLine("BoolMatrix Answer Count: {0}", count);
		}
		static void Usage(string exe)
		{
			Console.WriteLine("Usage: {0} <file>", exe);
			Console.WriteLine("\t<file>: The sudoku file path");
			Console.WriteLine("\tor using with stdin");
		}
		static int[] GetSudokuFromFile(StreamReader file)
		{
			try
			{
				int count = 0;
				int[] sudo = new int[SudokuLib.BOARD_SIZE];
				for (; count < SudokuLib.BOARD_SIZE;)
				{
					int c = file.Read();
					if (c >= '0' && c <= '9')
					{
						sudo[count] = c - '0';
						count++;
					}
				}
				return sudo;
			}
			catch (EndOfStreamException e)
			{
				Console.WriteLine(e);
				return null;
			}
		}
		static void DisplaySudoku(int[] board)
		{
			if (board.Length < SudokuLib.BOARD_SIZE)
			{
				return;
			}
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					int index = i * 9 + j;
					Console.Write("{0} ", board[index]);
					if (j == 2 || j == 5)
					{
						Console.Write(" ");
					}
				}
				Console.Write("\n");
				if (i == 2 || i == 5)
				{
					Console.Write("\n");
				}
			}
		}
		static void SolveDisplay(SolveProcedure proc)
		{
			Console.Write("Improve: {0} ", Sudoku.ImproveTypeName((ImproveType)proc.type));
			switch ((ImproveType)proc.type)
			{
				case ImproveType.DoNotImprove:
					Console.WriteLine("Do Not Improve");
					break;

				case ImproveType.Row2GridWith2Posibility:
				case ImproveType.Col2GridWith2Posibility:
				case ImproveType.Block2GridWith2Posibility:
					Console.WriteLine("gridOne: {0} {1}, gridTwo: {2} {3}, value: {4} {5}",
						   proc.gridOneX,
						   proc.gridOneY,
						   proc.gridTwoX,
						   proc.gridTwoY,
						   proc.numberOne,
						   proc.numberTwo);
					break;

				case ImproveType.Row3GridWith3Posibility:
				case ImproveType.Col3GridWith3Posibility:
				case ImproveType.Block3GridWith3Posibility:
					Console.WriteLine("gridOne: {0} {1}, gridTwo: {2} {3}, gridThree: {4} {5}, value: {6} {7} {8}",
						   proc.gridOneX,
						   proc.gridOneY,
						   proc.gridTwoX,
						   proc.gridTwoY,
						   proc.gridThreeX,
						   proc.gridThreeY,
						   proc.numberOne,
						   proc.numberTwo,
						   proc.numberThree);
					break;

				case ImproveType.Row2NumberIn2Grid:
				case ImproveType.Col2NumberIn2Grid:
				case ImproveType.Block2NumberIn2Grid:
					Console.WriteLine("value: {0} {1}, gridOne: {2} {3}, gridTwo: {4} {5}",
						   proc.numberOne,
						   proc.numberTwo,
						   proc.gridOneX,
						   proc.gridOneY,
						   proc.gridTwoX,
						   proc.gridTwoY);
					break;

				case ImproveType.Row3NumberIn3Grid:
				case ImproveType.Col3NumberIn3Grid:
				case ImproveType.Block3NumberIn3Grid:
					Console.WriteLine("value: {0} {1} {2}, gridOne: {3} {4}, gridTwo: {5} {6}, gridThree: {7} {8}",
						   proc.numberOne,
						   proc.numberThree,
						   proc.numberTwo,
						   proc.gridOneX,
						   proc.gridOneY,
						   proc.gridTwoX,
						   proc.gridTwoY,
						   proc.gridThreeX,
						   proc.gridThreeY);
					break;

				case ImproveType.InBlockNumberInOneRow:
				case ImproveType.InBlockNumberInOneCol:
					Console.WriteLine("block: {0} {1}, value: {2}, line: {3}", proc.panelRow, proc.panelCol, proc.number, proc.line);
					break;

				case ImproveType.InRowNumberInBlock:
				case ImproveType.InColNumberInBlock:
					Console.WriteLine("line: {0}, value: {1}, block: {2} {3}", proc.line, proc.number, proc.panelRow, proc.panelCol);
					break;

				case ImproveType.TwoRowOneNumberInTwoCol:
					Console.WriteLine("row: {0} {1}, value: {2}, column: {3} {4}",
						   proc.rowOne,
						   proc.rowTwo,
						   proc.number,
						   proc.colOne,
						   proc.colTwo);
					break;
				case ImproveType.TwoColOneNumberInTwoRow:
					Console.WriteLine("column: {0} {1}, value: {2}, row: {3} {4}",
						   proc.colOne,
						   proc.colTwo,
						   proc.number,
						   proc.rowOne,
						   proc.rowTwo);
					break;

				case ImproveType.ThreeRowOneNumberInThreeCol:
					Console.WriteLine("row: {0} {1} {2}, value: {3}, column: {4} {5} {6}",
						   proc.rowOne,
						   proc.rowTwo,
						   proc.rowThree,
						   proc.number,
						   proc.colOne,
						   proc.colTwo,
						   proc.colThree);
					break;
				case ImproveType.ThreeColOneNumberInThreeRow:
					Console.WriteLine("column: {0} {1} {2}, value: {3}, row: {4} {5} {6}",
						   proc.colOne,
						   proc.colTwo,
						   proc.colThree,
						   proc.number,
						   proc.rowOne,
						   proc.rowTwo,
						   proc.rowThree);
					break;
				default:
					Console.WriteLine("Do Not To Here: Default");
					break;
			}
		}
	}
}
