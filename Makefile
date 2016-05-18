scrabble.out : scrabble.cpp
	g++ -ansi -Wall -g -o scrabble.out scrabble.cpp

clean :
	rm -f scrabble.out
