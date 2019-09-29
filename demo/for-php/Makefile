.PHONY: for-php clean

for-php:
	cd phpsudoku && phpize && ./configure && make && sudo make install
	ldd phpsudoku/modules/phpsudoku.so

clean:
	cd phpsudoku && make clean
