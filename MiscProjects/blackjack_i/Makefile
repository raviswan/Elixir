black: deck.o dealer.o player.o main.o 
	g++ -std=c++14 deck.o dealer.o player.o main.o -o black
deck.o : deck.cpp blackjack.h
	g++ -std=c++14 -c deck.cpp
dealer.o : dealer.cpp dealer.h blackjack.h player.h
	g++ -std=c++14 -c dealer.cpp
player.o : player.cpp player.h dealer.h blackjack.h
	g++ -std=c++14 -c player.cpp
main.o : main.cpp dealer.h player.h blackjack.h
	g++ -std=c++14 -c main.cpp

clean:
	rm black deck.o main.o player.o dealer.o
