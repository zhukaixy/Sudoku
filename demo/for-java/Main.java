import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.FileReader;

class UsageMatrix implements IMatrixCallback {
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
}
class UsageSudoku implements ISudokuCallback {
	public int[] board = new int[SudokuLib.BOARD_SIZE];
	public int[] board_dancing = new int[SudokuLib.BOARD_SIZE];
	public boolean dancing = false;
	// row and col are in the range of 1-9
	public int SudokuReadData(int row, int col) {
		int index = (row - 1)*9+(col - 1);
		if (dancing) {
			return board_dancing[index];
		}
		return board[index];
	}
	// row col and value are in the range of 1-9
	public void SudokuWriteData(int row, int col, int value, int type) {
		int index = (row - 1)*9+(col - 1);
		if (dancing) {
			board_dancing[index] = value;
			return;			
		}
		board[index] = value;
		System.out.printf("Solve: %s row:%d column:%d value:%d\n", Sudoku.SolveTypeName(SolveType.values()[type]), row, col, value);
	}
	public void SolveProcessCallback(SolveProcedure proc) {
		System.out.printf("Improve: %s ", Sudoku.ImproveTypeName(ImproveType.values()[proc.type]));
		switch (ImproveType.values()[proc.type]) {
			case DoNotImprove:
			System.out.printf("Do Not Improve\n");
			break;

			case Row2GridWith2Posibility:
			case Col2GridWith2Posibility:
			case Block2GridWith2Posibility:
			System.out.printf("gridOne: %d %d, gridTwo: %d %d, value: %d %d\n",
					proc.gridOneX,
					proc.gridOneY,
					proc.gridTwoX,
					proc.gridTwoY,
					proc.numberOne,
					proc.numberTwo);
			break;

			case Row3GridWith3Posibility:
			case Col3GridWith3Posibility:
			case Block3GridWith3Posibility:
			System.out.printf("gridOne: %d %d, gridTwo: %d %d, gridThree: %d %d, value: %d %d %d\n",
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

			case Row2NumberIn2Grid:
			case Col2NumberIn2Grid:
			case Block2NumberIn2Grid:
			System.out.printf("value: %d %d, gridOne: %d %d, gridTwo: %d %d\n",
					proc.numberOne,
					proc.numberTwo,
					proc.gridOneX,
					proc.gridOneY,
					proc.gridTwoX,
					proc.gridTwoY);
			break;

			case Row3NumberIn3Grid:
			case Col3NumberIn3Grid:
			case Block3NumberIn3Grid:
			System.out.printf("value: %d %d %d, gridOne: %d %d, gridTwo: %d %d, gridThree: %d %d\n",
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

			case InBlockNumberInOneRow:
			case InBlockNumberInOneCol:
			System.out.printf("block: %d %d, value: %d, line: %d\n", proc.panelRow, proc.panelCol, proc.number, proc.line);
			break;

			case InRowNumberInBlock:
			case InColNumberInBlock:
			System.out.printf("line: %d, value: %d, block: %d %d\n", proc.line, proc.number, proc.panelRow, proc.panelCol);
			break;

			case TwoRowOneNumberInTwoCol:
			System.out.printf("row: %d %d, value: %d, column: %d %d\n",
					proc.rowOne,
					proc.rowTwo,
					proc.number,
					proc.colOne,
					proc.colTwo);
			break;
			case TwoColOneNumberInTwoRow:
			System.out.printf("column: %d %d, value: %d, row: %d %d\n",
					proc.colOne,
					proc.colTwo,
					proc.number,
					proc.rowOne,
					proc.rowTwo);
			break;

			case ThreeRowOneNumberInThreeCol:
			System.out.printf("row: %d %d %d, value: %d, column: %d %d %d\n",
					proc.rowOne,
					proc.rowTwo,
					proc.rowThree,
					proc.number,
					proc.colOne,
					proc.colTwo,
					proc.colThree);
			break;
			case ThreeColOneNumberInThreeRow:
			System.out.printf("column: %d %d %d, value: %d, row: %d %d %d\n",
					proc.colOne,
					proc.colTwo,
					proc.colThree,
					proc.number,
					proc.rowOne,
					proc.rowTwo,
					proc.rowThree);
			break;
			default:
			System.out.printf("Do Not To Here: Default\n");
			break;
		}
	}
	// ans is a null terminate char array
	public void SudokuAnswerCallback(int[] ans) {
		
	}
	public boolean GetSudokuFromFile(BufferedReader file) {
		try{
			int count = 0;
			for (; count < SudokuLib.BOARD_SIZE;) {
				int c = file.read();
				if (c == -1) {
					return false;
				}
				if (c >= '0' && c <= '9') {
					board[count] = c - '0';
					board_dancing[count] = c - '0';
					count++;
				}
			}
			return true;
		}catch(Exception e){
			e.printStackTrace();
			return false;
		}
	}
	public void DisplaySudoku(int[] board) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				int index = i * 9 + j;
				System.out.printf("%d ", board[index]);
				if (j == 2 || j == 5) {
					System.out.printf(" ");
				}
			}
			System.out.printf("\n");
			if (i == 2 || i == 5) {
				System.out.printf("\n");
			}
		}
	}
}
public class Main {
	public static void main(String[] args) {
		UsageMatrix useMat = new UsageMatrix();
		useMat.BoolMatrixUsage();
		int argc = args.length;
		if (argc != 0 && argc != 1) {
			Usage("java Main");
			System.exit(-1);
		}
		try{
			BufferedReader file = null;
			if (argc == 0) {
				file = new BufferedReader(new InputStreamReader(System.in));
			}else{
				file = new BufferedReader(new FileReader(args[0]));
			}
			UsageSudoku useSudo = new UsageSudoku();
			if (useSudo.GetSudokuFromFile(file) == false) {
				System.err.printf("Read sudoku from %s failed\n", args[0]);
				Usage("java Main");
				System.exit(-1);
			}

			useSudo.dancing = false;
			Sudoku sudo = new Sudoku(useSudo);
			int cnt = sudo.GetKnownCount();
			System.out.printf("Sudoku Known Count: %d\n", cnt);
			System.out.printf("Calculate step by step\n");
			int num = sudo.CalculateSudokuAll(false, useSudo);
			System.out.printf("Answer Count: %d\n", num);
			useSudo.DisplaySudoku(useSudo.board);
			boolean status = sudo.VerifySudokuBoard(useSudo.board);
			System.out.printf("Verify: %s\n", status ? "True" : "False");

			useSudo.dancing = true;
			System.out.printf("Calculate using dancing\n");
			num = sudo.CalculateSudokuAll(false, useSudo);
			System.out.printf("Answer Count: %d\n", num);
			System.out.printf("One of it:\n");
			useSudo.DisplaySudoku(useSudo.board_dancing);
			status = sudo.VerifySudokuBoard(useSudo.board);
			System.out.printf("Verify: %s\n", status ? "True" : "False");
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	static void Usage(String exec) {
		System.out.printf("Usage: %s <file>\n", exec);
		System.out.printf("\t<file>: The sudoku file path\n");
		System.out.printf("\tor using %s with stdin\n", exec);
	}
}
