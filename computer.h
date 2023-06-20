#ifndef __COMPUTER_H_
#define __COMPUTER_H_
#include "player.h"

class Computer : public Player {
	public:
	Computer();
	void setDiscard(std::vector<Card> dis);
	void setHand(std::vector<Card> hand); 
	bool humanType();
};

#endif
