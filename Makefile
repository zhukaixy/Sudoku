CC=g++

SudokuMain:SudokuMain.cpp SudokuClass.cpp SudokuClass.h
	$(CC) $^ -o $@
