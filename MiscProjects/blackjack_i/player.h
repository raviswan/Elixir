#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "blackjack.h"

class Player{
public:
	Player();
	void drawHand(const uint&, const uint&);
	void printHand() const;
	const uint& getHandValue() const;
	void checkSoftHand();
	void checkSoftHand(const uint&);
	uint playHand(const uint&);
	uint playHand();
	uint playHitCard(const uint&);
	float getWinPercentage() const;
	void updateResult(uint);
	void cleanup();
private:
	uint mRoundsPlayed;
	uint mWins;
	uint mLosses;
	vector<uint> mHand;
	uint mDealerCard;
	uint mHandValue;
};

#endif
