#ifndef __GAME_H_
#define __GAME_H_

#include <memory>
#include "player.h"


class Game
{
	std::vector<Card> deck;
	std::vector<Card> spades;
	std::vector<Card> hearts;
	std::vector<Card> clubs;
	std::vector<Card> diamonds;

	public:
	Game(); 
	void play(Card c); 
	void shuffle(int seed,std::vector<std::shared_ptr<Player>> p); 
	int first(std::vector<std::shared_ptr<Player>> p);
	bool validity(Card c); 
	void table(); 
	void getDeck(); 
	bool winner(std::vector<std::shared_ptr<Player>> p, std::vector<int>& g);
	void clearTable();
};

#endif
