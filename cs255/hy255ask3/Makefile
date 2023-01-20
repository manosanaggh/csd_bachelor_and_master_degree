make clean: testsymtab
	rm -rf testsymtab
make list: symtablelist.c testsymtab.c
	gcc -Wall -ansi -pedantic symtablelist.c testsymtab.c -o testsymtab
make hash: symtablehash.c testsymtab.c
	gcc -Wall -ansi -pedantic symtablehash.c testsymtab.c -o testsymtab
