#include "player.h"
#include <string>

extern PlayerAction pAction;

//Constructor
Player::Player():mRoundsPlayed(0), mWins(0),mLosses(0),
mDealerCard(0), mHandValue(0){
	mHand.clear();
}

void Player::drawHand(const uint& card1, const uint& card2) {
	char response;
	mHand.emplace_back(card1);
	mHand.emplace_back(card2);
	mHandValue = mHand[0] + mHand[1];
	printHand();
	if (mHandValue != 21){
		checkSoftHand();
	}
}

void Player::printHand() const{
	cout<<"Face values of Player hand:  "<<mHand[0]<<" & "<<mHand[1]<<endl;
}

const uint& Player::getHandValue() const {
	return mHandValue;
}

void Player::checkSoftHand(){
	char response;
	if (mHand[0] == 11 || mHand[1] == 11){
		cout<<"\nTreat Ace (i.e. face value of 11) as 1 ? Type 'y' or 'n': ";
		cin>>response;
		if(response == 'y'){
			switch (mHandValue) {
				case 22:
					mHandValue = 12;
					break;
				default:
					mHandValue = (mHand[0] == 11)? mHand[1]+1 : mHand[0]+1;
					break;
			}
		}
		if(response != 'n' && response != 'y' ){
			checkSoftHand();
		}
	}
}

//Check soft hand for every hit card
void Player::checkSoftHand(const uint& card){
	char response;
	if (card == 11){
		cout<<"Treat Ace (i.e. face value of 11) as 1 ? Type 'y' or 'n': ";
		cin>>response;
		if(response == 'y'){
			++mHandValue;
		}
		else if (response == 'n'){
			mHandValue += card;
		}
		else{
			checkSoftHand(card);
		}
	}
	else{
		mHandValue += card;
	}
}

uint Player::playHand(const uint& c){
	mDealerCard = c;
	cout<<"Face value of Dealer Up card: "<<mDealerCard<<endl;
	return playHand();
}

uint Player::playHand(){
	char input;
	uint retVal;
	if (mHandValue == 21){
		pAction = blackjack;
	}
	else if(mHandValue > 21){
		pAction = busted;
	}
	else{
		cout<<"What do you want to do: Press h for 'Hit'; s for 'Stand': ";
		cin>>input;
		switch (input) {
			case 'h':
				pAction = hit;
				break;
			case 's':
				pAction = stand;
				break;
			default:
				cout<<"Invalid input. Try again\n";
				pAction = static_cast<PlayerAction>(playHand());
		}
	}
	return static_cast<uint>(pAction);
}

uint Player::playHitCard(const uint& card){
	cout<<"Player hit card has face value: "<<card<<endl;
	mHand.emplace_back(card);
	checkSoftHand(mHand.back());
	return playHand();
}

float Player::getWinPercentage() const {
	return 100*((float)mWins/mRoundsPlayed);
}

void Player::updateResult(uint val){
	++mRoundsPlayed;
	//the dealer updates us to indicate we won, or lost or tied.
	switch (val){
		case 0:
			++mLosses;
			break;
		case 1:
			++mWins;
			break;
		default:
			break;
	}
	
}

void Player::cleanup(){
	mHand.clear();
	mHandValue = 0;
	mDealerCard = 0;
}
