hello: hello.c
	gcc -ansi -pedantic -Wall -static -g hello.c -o hello

data3: createdata3.c
	gcc -ansi -pedantic -Wall createdata3.c -o createdata3
	createdata3 > data3

data6: createdata6.c
	gcc -ansi -pedantic -Wall createdata6.c -o createdata6
	createdata6 > data6

data9: createdata9.c
	gcc -ansi -pedantic -Wall createdata9.c -o createdata9
	createdata9 > data9

clean: hello createdata3 createdata6 createdata9 data3 data6 data9
	rm -rf hello
	rm -rf createdata3 
	rm -rf createdata6 
	rm -rf createdata9 
	rm -rf data3 
	rm -rf data6 
	rm -rf data9

all: createdata3.c createdata6.c createdata9.c
	gcc -ansi -pedantic -Wall createdata3.c -o createdata3
	createdata3 > data3
	gcc -ansi -pedantic -Wall createdata6.c -o createdata6
	createdata6 > data6
	gcc -ansi -pedantic -Wall createdata9.c -o createdata9
	createdata9 > data9

