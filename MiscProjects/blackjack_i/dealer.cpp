#include "dealer.h"
#include <ctime>

extern PlayerAction pAction;
extern DealerAction dAction;

Dealer::Dealer(Deck* deck):mSoftHand(false), mHandValue(0), mDeckPtr(deck){	
	mDealerHand.clear();	
}

Dealer::~Dealer(){
}

uint Dealer::drawCard(){
	return mDeckPtr->drawCard();
}

const uint& Dealer::drawDealerHand(){
	const uint& c1 = drawCard();
	const uint& c2 = drawCard();
	mDealerHand.emplace_back(c1);
	mDealerHand.emplace_back(c2);
	mHandValue = mDealerHand[0] + mDealerHand[1];
	mUpCard = mDealerHand[0];
	checkDealerSoftHand();
	return mUpCard;
}

void Dealer::drawPlayerHand(Player* p){
	const uint& c1 = drawCard();
	const uint& c2 = drawCard();
	p->drawHand(c1, c2);
}

const uint& Dealer::getHandValue() const{
	return mHandValue;
}

void Dealer::printHand() const{
	for(auto&i : mDealerHand){
		cout<<i<< " ";
	}
}

//Check whether dealer hand is soft or not
void Dealer::checkDealerSoftHand(){
	if (mDealerHand[0] == 11 || mDealerHand[1] == 11){
		mSoftHand = true;
		switch (mDealerHand[0] + mDealerHand[1]){
			case 22:
				mHandValue = 12;
				break;
			default:
				break;
		}
	}
	else {
		mSoftHand = false;
	}
}

//Check soft hand for every hit card
void Dealer::checkDealerSoftHand(const uint& card){
	if (card == 11){
		mSoftHand = true;
		uint newVal = mHandValue + card;
		if (newVal <= 21){
			mHandValue += card;
		}
		else {
			++mHandValue;
		}
	}
	else{
		mHandValue += card;
	}
}

uint Dealer::getPlayerHitCard(){
	return drawCard();
}

//If player is busted, then dealer wins by default
uint Dealer::dealerAction(uint pVal){
	if(pVal == busted){
		dAction = d_no_op;
		return dAction;
	}
	return dealerAction();
}

//all dealer actions take place here. Hit on Soft 17 
uint Dealer::dealerAction(){
	if (mHandValue == 21){
		dAction = d_blackjack;
	}
	else if (mHandValue > 21){	
		dAction = d_busted;
	}
	else if(!mSoftHand && mHandValue <= 16){
		mDealerHand.emplace_back(drawCard());
		checkDealerSoftHand(mDealerHand.back());
		dealerAction();
	}
	//hit on Soft-17
	else if(mSoftHand && mHandValue <= 17){
		mDealerHand.emplace_back(drawCard());
		checkDealerSoftHand(mDealerHand.back());
		dealerAction();
	}
	else{
		dAction = d_stand;
	}
	return static_cast<uint>(dAction);
}

//Clean-up before every round
void Dealer::cleanup(){
	mHandValue = 0;
	mUpCard = 0;
	mSoftHand = false;
	mDealerHand.clear();
	mDeckPtr->putBackPlayedCards();
}
