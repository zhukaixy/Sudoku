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
			Console.WriteLine("argc: {0}", argc);
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
			foreach (var item in board)
			{
				Console.Write(item);
			}
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
				Console.WriteLine("In Callback Now");
				Console.Write("Answer: ");
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
				int[] sudo = new int[81];
				for (; count < 81;)
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
	}
}
