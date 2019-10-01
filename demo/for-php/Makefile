.PHONY: for-php run clean

for-php:
	cd phpsudoku && phpize && ./configure && make && sudo make install
	ldd phpsudoku/modules/phpsudoku.so

run:
	php main.php ../../data/1.sudoku

clean:
	cd phpsudoku && make clean
