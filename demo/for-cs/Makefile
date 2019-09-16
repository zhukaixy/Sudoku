.PHONY: for-cs run linuxrun clean

for-cs:
	xbuild for-cs.sln
# msbuild for-cs.sln

run:
	LD_LIBRARY_PATH=../../buildXcode/sudoku/Debug/ mono ./lib/Debug/for-cs.exe ../../data/1.sudoku

linuxrun:
	LD_LIBRARY_PATH=../../build/sudoku/ mono ./lib/Debug/for-cs.exe ../../data/1.sudoku

clean:
	rm -rf obj lib
