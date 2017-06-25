#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <vector>
#include <map>
#include <array>

using namespace std;

enum class action : int{
	No_op =0,
	Hit, 
	Stand
};
using actionArray = array<action,12>;


class Player{
public:
	Player(uint bet);
	void setBet(uint);
	void getHand(uint&, uint&) const;
	uint getHandValue() const;
	float getWinPercentage() const;
	void updateResult(uint);
	void drawHand(uint, uint);
	action playHand(uint);
	action playHitCard(uint card, uint dealerCard);
	void formulate_strategy();
	void cleanup();
	void checkSoftHand(uint,uint);
	bool isBlackJack();
private:
	uint mBet;
	uint mRoundsPlayed;
	uint mWins;
	uint mLosses;
	vector<uint> mHand;
	uint mHandValue;
	bool mSoftHand;
	map<uint, actionArray> mMap;
	map<uint, actionArray> mSoftMap;
};

#endif
