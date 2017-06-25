#include "deck.h"
#include <ctime>

//Card specs
const uint NUM_SUITS = 4;
const uint SUIT_CARDS = 13;
const uint CARD_COUNT = NUM_SUITS*SUIT_CARDS;
array<uint,SUIT_CARDS> suit = {2,3,4,5,6,7,8,9,10,10,10,10,11};

Deck::Deck(){
	for(uint j = 0; j < NUM_SUITS ; ++j){
		for(uint k = 0 ; k < SUIT_CARDS; ++k){
			mDeck.emplace_back(suit[k]);
		}
	}
}

uint Deck::drawCard(){
	uint playCard = mDeck.front();
	mDrawnCards.emplace_back(playCard);
	mDeck.erase(mDeck.begin());
	return playCard;
}

void Deck::shuffleDeck(){
	srand(time(NULL));
	uint toIndex;
	uint fromIndex;
	uint temp;
	//Shuffle by taking two random cards and swapping them. Repeat this  
	//a number of times
	for(uint i = 0; i < CARD_COUNT ; ++i){
		fromIndex = rand() % CARD_COUNT;
		toIndex = rand() % CARD_COUNT;
		temp = mDeck[toIndex];
		mDeck[toIndex] = mDeck[fromIndex];
		mDeck[fromIndex] = temp;
	}
}

void Deck::printDeck(){
	cout<<"\nDeck\n"<<endl;
	for(uint i = 0; i < CARD_COUNT ; ++i){
		cout<<mDeck[i]<<endl;
	}
}

void Deck::printSortedDeck(){
	sort(mDeck.begin(),mDeck.end());
	cout<<"\nSorted mDeck\n"<<endl;
	for(uint i = 0; i < CARD_COUNT ; ++i){
		cout<<mDeck[i]<<endl;
	}
}

//Played cards are added to the back of the playing deck
//so before the cards repeat, they would have been shuffled
void Deck::putBackPlayedCards(){
	for(auto& c : mDrawnCards){
		mDeck.emplace_back(c);
	}
	mDrawnCards.clear();
}



