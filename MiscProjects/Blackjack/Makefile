black: dealer.o player.o main.o 
	g++ -std=c++14 -o black dealer.o player.o main.o

dealer.o : dealer.cpp dealer.h
	g++ -std=c++14 -c dealer.cpp
player.o : player.cpp player.h dealer.h
	g++ -std=c++14 -c player.cpp
main.o : main.cpp dealer.h
	g++ -std=c++14 -c main.cpp

clean:
	rm black main.o player.o dealer.o