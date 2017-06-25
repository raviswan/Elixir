#include "player.h"
#include <iostream>
#include <vector>


//hard hand strategy
actionArray p4_11 = 	{action::No_op,action::No_op,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit};
actionArray p12 = 		{action::No_op,action::No_op,action::Hit,action::Hit,action::Stand,action::Stand,action::Stand,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit};
actionArray p13_16 = 	{action::No_op,action::No_op,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit};
actionArray p17_20 = 	{action::No_op,action::No_op,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand};
actionArray p21_over = 	{action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op};

//soft hand strategy
actionArray s3_17 = 	{action::No_op,action::No_op,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit,action::Hit};
actionArray s18 = 		{action::No_op,action::No_op,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Hit,action::Hit,action::Hit};
actionArray s19_20 = 	{action::No_op,action::No_op,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand,action::Stand};
actionArray s21_over = 	{action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op,action::No_op};

//Constructor
Player::Player(uint bet):mBet(bet),mSoftHand(false),mRoundsPlayed(0),
mWins(0),mLosses(0){
	formulate_strategy();
}

void Player::setBet(uint amount) {
	mBet = amount;
}

void Player::drawHand(uint card1, uint card2) {
	mHand.emplace_back(card1);
	mHand.emplace_back(card2);
	if(isBlackJack()){
		mHandValue = 21;
	}
	else{
		if (card1 == 11 || card2 == 11){
			cout<<"Player got soft hand: "<<card1<<" & "<<card2<<endl;
			checkSoftHand(card1, card2);
			cout<<"Player soft hand face value: "<<mHandValue<<endl;
		}
		else{
			mHandValue = card1 + card2;
		}
	}
	
}

bool Player::isBlackJack(){
	return (mHand[0] + mHand[1]) == 21 ?  true : false;
}
void Player::checkSoftHand(uint card1,uint card2){
	switch (card1+card2){
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			mHandValue = (card1 == 11)? ++card2 : ++card1;
			mSoftHand = true;
			break;
		case 22:
			//If it's both Ace and Ace,make one of them soft
			mHandValue = 12;
			mSoftHand = true;
			break;
		default:
			mHandValue = card1 + card2;
			mSoftHand = false;
			break;
	}
}

//This index into the map and extracts the action to be relayed to the dealer
action Player::playHand(uint dealerCard){
	actionArray a;
	if(mSoftHand){
		a = mSoftMap[mHandValue];
	}
	else{
		a = mMap[mHandValue];
	}
	return a[dealerCard];
}

action Player::playHitCard(uint card, uint dealerCard){
	mHand.emplace_back(card);
	mHandValue += card;
	if(mHandValue == 21){
		return action::No_op;
	}
	return playHand(dealerCard);
}

uint Player::getHandValue() const{
	return mHandValue;
}

void Player::getHand(uint& card0, uint& card1) const{
	card0 = mHand[0];
	card1 = mHand[1];
}

float Player::getWinPercentage() const{
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
	mBet = 0;
	mHand.clear();
	mHandValue = 0;
	mSoftHand = false;
}

//This strategy is for single deck , single player.
void Player::formulate_strategy(){
		//hard hand..min is 2+2=4
		for(int i = 4; i <= 11; ++i){
			mMap.insert(make_pair(i,p4_11));
		}
		//soft hand, min. = Ace+2 = 3
		for(int i = 3; i <= 12; ++i){
			mSoftMap.insert(make_pair(i,s3_17));
		}
		for(int i = 13; i <= 16; ++i){
			mMap.insert(make_pair(i,p13_16));
			mSoftMap.insert(make_pair(i,s3_17));
		}
		for(int i = 19; i <= 20; ++i){
			mMap.insert(make_pair(i,p17_20));
			mSoftMap.insert(make_pair(i,s19_20));
		}
		for(int i = 21; i <= 33; ++i){
			mMap.insert(make_pair(i,p21_over));
			mSoftMap.insert(make_pair(i,s21_over));
		}
		mMap.insert(make_pair(12,p12));
		mMap.insert(make_pair(17,p17_20));
		mMap.insert(make_pair(18,p17_20));

		mSoftMap.insert(make_pair(17,s3_17));
		mSoftMap.insert(make_pair(18,s18));
}
