#include "blackjack.h"
#include "dealer.h"
#include "player.h"
#include "deck.h"

DealerAction dAction = d_no_op;
PlayerAction pAction = no_op;
Result res = Push;

void findWinner(Dealer* dealer, uint dValue, 
	Player* player, uint pValue){
	dAction = static_cast<DealerAction>(dValue);
	pAction = static_cast<PlayerAction>(pValue);
	cout<<"============================================================\n";
	if(pAction == blackjack && dAction == d_blackjack){
		cout<<"Both player and dealer have blackjack. Neither won"<<endl;
		res = Push;
	}
	else if (pAction == blackjack && dAction != d_blackjack){
		cout<<"Player has blackjack. Player won"<<endl;
		res = Won;
	}
	else if (pAction != blackjack && dAction == d_blackjack){
		cout<<"Dealer has blackjack. Player lost"<<endl;
		res = Lost;
	}
	else if (pAction == busted){
		cout<<"Player busted with a hand: "<<player->getHandValue()
		<<". Player lost"<<endl;
		res = Lost;
	}
	else if (dAction == d_busted){
		cout<<"Dealer Busted! Player hand: "<<player->getHandValue()
		<<". Dealer hand "<<dealer->getHandValue()<<"\nPlayer won"<<endl;
		res = Won;
	}
	else{
		const uint& pVal = player->getHandValue();
		const uint& dVal = dealer->getHandValue();
		if(pVal == dVal){
			cout<<"Both player and dealer got: "<<pVal<<". Neither won"<<endl;
			res = Push;
		}
		else if (pVal > dVal){
			cout<<"Player got: "<<pVal<<". Dealer got: "<<dVal<<". Player won"<<endl;
			res = Won;
		}
		else{
			cout<<"Player got: "<<pVal<<". Dealer got: "<<dVal<<". Player lost"<<endl;
			res = Lost;
		}
	}
	cout<<"Dealer cards are: ";
	dealer->printHand();
	player->updateResult(res);
	cout<<"\nPlayer winning %: "<<player->getWinPercentage();
	cout<<"\n============================================================\n";
}

void playGame(Deck* deck, Dealer* d, Player* p){
	uint pAction;
	uint dAction;
	uint shufIndex = 0;
	uint upCard;
	uint hitCard;
	char response;
	cout<<"Start a round of blackjack? Hit 'y' or 'n':  ";
	cin>>response;

	//Rounds start below
	while(response != 'n'){
		cout<<"\n\n-------------------------ROUND "<<shufIndex+1<<"----------------------------\n";
		if (!(shufIndex % 6)){
			deck->shuffleDeck();
			cout<<"Deck shuffled\n";
		}
		d->drawPlayerHand(p);
		upCard = d->drawDealerHand();
		pAction = p->playHand(upCard);
		while(pAction == hit){
			hitCard = d->getPlayerHitCard();
			pAction = p->playHitCard(hitCard);
		}
		dAction = d->dealerAction(pAction);
		findWinner(d, dAction, p, pAction);
		d->cleanup();
		p->cleanup();
		++shufIndex;
		cout<<"Play another round of blackjack? Hit 'y' or 'n': ";
		cin>>response;
	}
}
int main(int argc, char** argv){
	Deck deck;
	Dealer d(&deck);
	Player p;
	playGame(&deck, &d, &p);
	return EXIT_SUCCESS;
}