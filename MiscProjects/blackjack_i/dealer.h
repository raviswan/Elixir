#ifndef _DEALER_H_
#define _DEALER_H_

#include "blackjack.h"
#include "deck.h"
#include "player.h"

class Player;
class Deck;
         
class Dealer{
public:
	Dealer(Deck*);
	~Dealer();
	uint drawCard();
	const uint& drawDealerHand();
	void drawPlayerHand(Player*);
	const uint& getHandValue() const;
	void printHand() const;
	void checkDealerSoftHand();
	void checkDealerSoftHand(const uint&);
	uint getPlayerHitCard();
	uint dealerAction();
	uint dealerAction(uint);
	void cleanup();
private:
	vector<uint> mDealerHand;
	uint mUpCard;
	uint mHandValue;	
	Deck* mDeckPtr;
	bool mSoftHand;
};


#endif