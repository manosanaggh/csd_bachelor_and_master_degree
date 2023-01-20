clean:
	rm -rf a.out
	rm -rf lala.cpp
	rm -rf parser.output
	rm -rf parser.cpp
	rm -rf parser.hpp
	rm -rf alpha
	rm -rf target_code.txt
	rm -rf binary_file.dat
	rm -rf binary_file.txt 
	rm -rf proxeiro.txt
	rm -rf toDO.txt
all:
	clear
	flex --outfile=lala.cpp alpha_lex.l
	bison --yacc --defines --output=parser.cpp parserFINALNOCONFLICTS.y -v
	g++ -g -w lala.cpp parser.cpp

avm:
	clear
	g++ -g -w avm.cpp -o alpha
