#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "card.h"

class Player
{
	protected:
	int score;
	std::vector<Card> handcards;
	std::vector<Card> discards;
	std::vector<Card> valid;

	public:
    Player();
	void play(Card c);
	void discard(Card c);
	void dealCard(Card c); 
	std::vector<Card> getHandCard(); 
	std::vector<Card> getDiscard(); 
	std::vector<Card> getValid();
	void updateValid(std::vector<Card> c);
	int getScore();
	void addScore(int n); 
	void clear();
	virtual bool humanType() = 0; 
};

#endif
