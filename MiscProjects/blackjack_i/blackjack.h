#ifndef _BLACKJACK_H_
#define _BLACKJACK_H_

#include <iostream>
#include <array>
#include <vector>
#include <map>

using namespace std;

typedef unsigned int uint;

enum PlayerAction{
	no_op = 100,
	hit, 
	stand,
	blackjack,
	busted
};
extern PlayerAction pAction;

enum DealerAction{
	d_no_op = 200, 
	d_hit,
	d_stand,
	d_blackjack,
	d_busted
};
extern DealerAction dAction;


enum Result {
	Lost = 0,
	Won,
	Push
};
extern Result res;

#endif
