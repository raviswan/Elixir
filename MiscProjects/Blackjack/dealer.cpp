#include "dealer.h"
#include <ctime>

//Configuration parameters
const uint PLAYER_COUNT = 1;
const uint NUM_DECKS = 1;
const uint NUM_ROUNDS = 13;
const uint NUM_SUITS = 4;
const uint SUIT_CARDS = 13;
const uint CARD_COUNT = NUM_DECKS*NUM_SUITS*SUIT_CARDS;
const uint DEALER_BET = 100;
const uint PLAYER_BET = 100;
array<uint,SUIT_CARDS> suit = {2,3,4,5,6,7,8,9,10,10,10,10,11};
int Dealer::randomSeed = time(NULL);


Dealer::Dealer():mSoftHand(false),mDealerBet(0),mDealerCard(0){
	createPlayingDeck();
	setDealerBet(DEALER_BET);
}

Dealer::~Dealer(){
	for(uint i=1;i<=PLAYER_COUNT;++i){
		delete mPlayers[i];
	}
}
void Dealer::createPlayingDeck(){
	for(uint i = 0; i < NUM_DECKS; ++i){
		for(uint j = 0; j < NUM_SUITS ; ++j){
			for(uint k = 0 ; k < SUIT_CARDS; ++k){
				mDeck.emplace_back(suit[k]);
			}
		}
	}
}

//Can support multiple players
void Dealer::initializePlayers(){
	for(uint i=1;i<=PLAYER_COUNT;++i){
		Player* p = new Player(100);
		mPlayers.insert(make_pair(i,p));
	}
}

void Dealer::setPlayerBets(uint PLAYER_BET){
	for(uint i=1;i<=PLAYER_COUNT;++i){
		mPlayers[i]->setBet(PLAYER_BET);
	}
}

void Dealer::setDealerBet(uint bet){
	this->mDealerBet = bet;
}

uint Dealer::getDealerBet() const{
	return this->mDealerBet;
}

uint Dealer::drawCard(){
	uint playCard = mDeck.front();
	mDrawnCards.emplace_back(playCard);
	mDeck.erase(mDeck.begin());
	return playCard;
}

void Dealer::drawDealerHand(){
	mDealerHand.emplace_back(drawCard());
	mDealerHand.emplace_back(drawCard());
	mDealerCard = mDealerHand[1];
	mHandValue = mDealerHand[0] + mDealerHand[1];
	cout<<"Dealer cards: "<<mDealerHand[0]<<" & "<<mDealerHand[1]<<endl;
	if ( mHandValue != 21 ){
		if (mDealerHand[0] == 11 || mDealerHand[1] == 11){
			cout<<"Dealer got soft hand: "<<mDealerHand[0]<<" & "<<
			mDealerHand[1]<<endl;
			checkDealerSoftHand(mDealerHand[0], mDealerHand[1]);
			cout<<"Dealer soft hand face value: "<<mHandValue<<endl;
		}
	}

}

void Dealer::checkDealerSoftHand(uint card1, uint card2){
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
const vector<uint>& Dealer::showDealerHand(){
	return mDealerHand;
}

void Dealer::drawPlayerHands(){
	uint c0,c1;
	for (uint i=1;i<=PLAYER_COUNT;++i){
		mPlayers[i]->drawHand(drawCard(),drawCard());
		mPlayers[i]->getHand(c0,c1);
		cout<<"Player "<<i<<" has cards with face value: "<<c0<<" & "<<c1<<endl;
	}

}

void Dealer::printDeck(){
	cout<<"\nDeck\n"<<endl;
	for(uint i = 0; i < CARD_COUNT ; ++i){
		cout<<mDeck[i]<<endl;
	}
}

void Dealer::printSortedDeck(){
	sort(mDeck.begin(),mDeck.end());
	cout<<"\nSorted mDeck\n"<<endl;
	for(uint i = 0; i < CARD_COUNT ; ++i){
		cout<<mDeck[i]<<endl;
	}
}

void Dealer::shuffleDeck(){
	++Dealer::randomSeed;
	srand(Dealer::randomSeed);
	uint toIndex;
	uint fromIndex;
	uint temp;
	//Shuffle by taking two random cards and swapping them. Do this 
	//many times. I chose to do it 52 times
	for(uint i = 0; i < CARD_COUNT ; ++i){
		fromIndex = rand() % CARD_COUNT;
		toIndex = rand() % CARD_COUNT;
		temp = mDeck[toIndex];
		mDeck[toIndex] = mDeck[fromIndex];
		mDeck[fromIndex] = temp;
	}
}

//Played cards in a given round are added to the back of the playing deck
//so before the cards repeat, they would have been shuffled
void Dealer::putBackPlayedCards(){
	for(auto& c : mDrawnCards){
		mDeck.emplace_back(c);
	}
}

//This function handles the player  directive to Hit, Stand.If it's a hit,
//the function is called recursively, if it's a Stand, dealer will take action
//by calling dealerAction()
void Dealer::actOnPlayerRequest(uint pIndex, PlayerAction pAction){
	if(pAction == PlayerAction::Hit){
		uint hitCard = drawCard();
		cout<<"Player "<<pIndex<<" HIT card has a face value: "<<hitCard<<endl;
		PlayerAction newAction = 
		static_cast<PlayerAction>(mPlayers[pIndex]->playHitCard(hitCard,
			mDealerCard));
		actOnPlayerRequest(pIndex,newAction);
	}
	else if(pAction == PlayerAction::Stand){
		cout<<"Player "<<pIndex<<" requested STAND with total hand: "<<
		mPlayers[pIndex]->getHandValue()<<endl;
		dealerAction(pIndex);
	}
	else{
		if(mPlayers[pIndex]->getHandValue() > 21){
			mPlayers[pIndex]->updateResult(0);
			cout<<"Busted! Player "<<pIndex<<" lost \n";
			cout<<"Player winning % = "<<mPlayers[pIndex]->getWinPercentage()<<endl;
		}
		else if(mPlayers[pIndex]->getHandValue() == 21){
			cout<<"Blackjack!!! Player "<<pIndex<<" won\n";
			mPlayers[pIndex]->updateResult(1);
			cout<<"Player winning % = "<<mPlayers[pIndex]->getWinPercentage()<<endl;
		}
		else{
			cout<<"incorrect operation\n";
		}
	}
}

//all dealer actions take place here. Hit on Soft 17 is taken care of
void Dealer::dealerAction(uint pIndex){
	uint pValue = mPlayers[pIndex]->getHandValue();
	if (mHandValue == 21){
		cout<<"Dealer got a blackjack.\n";
		mPlayers[pIndex]->updateResult(0);
		cout<<"Player "<<pIndex<<" lost\n";
		cout<<"Player winning % = "<<mPlayers[pIndex]->getWinPercentage()<<endl;
	}
	else if (mHandValue > 21){
		mPlayers[pIndex]->updateResult(1);
		cout<<"Dealer busted with face value: "<<mHandValue<<"\n"<<
		"Player "<<pIndex<<" won\n";
		cout<<"Player winning % = "<<mPlayers[pIndex]->getWinPercentage()<<endl;
	}
	else if(!mSoftHand && mHandValue <= 16){
		mHandValue += drawCard();
		cout<<"Dealer needed to hit! Total new face value: "<<mHandValue<<endl;
		dealerAction(pIndex);
	}
	//hit on Soft-17
	else if(mSoftHand && mHandValue <= 17){
		mHandValue += drawCard();
		cout<<"Dealer needed to soft hit! Total new face value: "<<mHandValue<<endl;
		dealerAction(pIndex);
	}
	else {
		//player lost
		if(mHandValue > pValue){
			mPlayers[pIndex]->updateResult(0);
			cout<<"Dealer total face value: "<<mHandValue<<endl;
			cout<<"Player "<<pIndex<<" lost\n";
			cout<<"Player winning % = "<<mPlayers[pIndex]->getWinPercentage()<<endl;
		}
		//player won
		else if(mHandValue < pValue){
			mPlayers[pIndex]->updateResult(1);
			cout<<"Dealer total face value: "<<mHandValue<<endl;
			cout<<"Player "<<pIndex<<" won\n";
			cout<<"Player winning % = "<<mPlayers[pIndex]->getWinPercentage()<<endl;
		}
		//tie
		else{
			mPlayers[pIndex]->updateResult(2);
			cout<<"Dealer total face value: "<<mHandValue<<endl;
			cout<<"Player "<<pIndex<<" neither won or lost\n";
			cout<<"Player winning % = "<<mPlayers[pIndex]->getWinPercentage()<<endl;
		}
	}

}

//Clean-up before every round
void Dealer::cleanup(){
	mDealerBet = 0;
	mDealerCard = 0;
	mSoftHand = false;
	putBackPlayedCards();
	mDealerHand.clear();
	mDrawnCards.clear();
	for (uint i=1;i<=PLAYER_COUNT;++i){
		mPlayers[i]->cleanup();
	}

}


void Dealer::playGame(){
	initializePlayers();
	PlayerAction pAction;
	//Rounds start below
	for(uint rIndex = 0,shufIndex = 0 ; shufIndex= rIndex % 6,rIndex < NUM_ROUNDS ; ++rIndex){
		cout<<"\n----------------------Round "<<rIndex<<"--------------------\n";
		if(!shufIndex){
			cout<<"Deck Shuffled\n";
			shuffleDeck();
		}
		setDealerBet(DEALER_BET);
		setPlayerBets(PLAYER_BET);
		drawPlayerHands();
		drawDealerHand();
		cout<<"Dealer open card has face value: "<<mDealerCard<<endl;	
		for (uint pIndex = 1; pIndex <= PLAYER_COUNT; ++pIndex){
			if(mPlayers[pIndex]->isBlackJack()){
				cout<<"Blackjack!!! Player "<<pIndex<<" won\n";
				mPlayers[pIndex]->updateResult(1);
				cout<<"Player winning % = "<<mPlayers[pIndex]->getWinPercentage()<<endl;
			}
			else{
				pAction = static_cast<PlayerAction>(
					mPlayers[pIndex]->playHand(mDealerCard)
					);
				actOnPlayerRequest(pIndex, pAction);
			}
			cout<<"\n";
		}
		cleanup();
	}
}