.PHONY: for-cs run

for-cs:
	xbuild for-cs.sln
	# msbuild for-cs.sln

run:
	LD_LIBRARY_PATH=../../buildXcode/sudoku/Debug/ mono ./lib/Debug/for-cs.exe ../../data/1.sudoku
	# LD_LIBRARY_PATH=../../build/sudoku/Debug/ mono ./lib/Debug/for-cs.exe ../../data/1.sudoku
