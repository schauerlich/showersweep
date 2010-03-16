minesweeper.out : main.o board.o box.o
	g++ -Wall -ansi -g -o minesweeper.out main.o board.o box.o

main.o : main.cpp board.h
	g++ -Wall -ansi -g -c main.cpp

board.o : board.cpp board.h box.h
	g++ -Wall -ansi -g -c board.cpp

box.o : box.cpp box.h
	g++ -Wall -ansi -g -c box.cpp


clean : 
	rm minesweeper.out main.o board.o box.o