#ifndef _DECK_H_
#define _DECK_H_

#include "blackjack.h"
class Deck{
public:
	Deck();
	uint drawCard();
	uint getDeckSize(){ return mDeck.size();}
	void shuffleDeck();
	void printDeck();
	void printSortedDeck();
	void putBackPlayedCards();
private:
	vector<uint> mDeck;
	vector<uint> mDrawnCards;
};


#endif