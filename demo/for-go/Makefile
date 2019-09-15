.PHONY: for-go run clean

for-go:
	go build -o ./build/for-go
# GOOS=windows GOARCH=amd64
# GOOS=linux GOARCH=amd64
# GOOS=darwin GOARCH=amd64

run:
	LD_LIBRARY_PATH=../../buildXcode/sudoku/Debug/ ./build/for-go ../../data/1.sudoku
# LD_LIBRARY_PATH=../../build/sudoku/Debug/ mono ./lib/Debug/for-cs.exe ../../data/1.sudoku

clean:
	rm -f ./build/for-go
