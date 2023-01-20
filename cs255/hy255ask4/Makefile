clean: sudoku
	rm -rf sudoku

sudoku: grid.h sudoku.h grid.c sudoku.c
	gcc -ansi -pedantic -Wall grid.c sudoku.c -o sudoku 

