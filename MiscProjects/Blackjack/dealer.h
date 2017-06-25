#ifndef _DEALER_H_
#define _DEALER_H_

#include <iostream>
#include <array>
#include <vector>
#include <map>
#include "player.h"

using namespace std;
using uint = unsigned int;
class Player;
enum class PlayerAction: int{
	No_op =0,
	Hit = 1, 
	Stand
};
         
class Dealer{
public:
	Dealer();
	~Dealer();
	void initializePlayers();
	uint drawCard();
	void drawDealerHand();
	const vector<uint>& showDealerHand();
	void drawPlayerHands();
	void setDealerBet(uint);
	uint getDealerBet() const;
	void setPlayerBets(uint);
	void createPlayingDeck();
	void shuffleDeck();
	void playGame();
	void printDeck();
	void printSortedDeck();
	void putBackPlayedCards();
	void actOnPlayerRequest(uint, PlayerAction);
	void dealerAction(uint);
	void cleanup();
	void checkDealerSoftHand(uint, uint);


private:
	vector<uint> mDealerHand;
	uint mDealerCard;
	uint mHandValue;
	//Player index will identify the player,and get access to their info
	map<uint,Player* > mPlayers;	
	uint mDealerBet;
	vector<uint> mDeck;
	vector<uint> mDrawnCards;
	bool mSoftHand;
	static int randomSeed;
};


#endif