#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include "game.h"

Game::Game()
{
    for(int i = 0; i < 4; i++){
        for (int j = 1; j < 14; j++){
            if(i == 0) {
                Card c{j,'C'}; 
                deck.emplace_back(c);
            }
            if(i == 1) {
                Card c{j,'D'}; 
                deck.emplace_back(c);
            }
            if(i == 2) {
                Card c{j,'H'}; 
                deck.emplace_back(c);
            }
            if(i == 3) {
                Card c{j,'S'}; 
                deck.emplace_back(c);
            }
        }
    }
}

void Game::play(Card c) {
    char suit = c.getSuit();
    int rank = c.getRankNum();

    if(validity(c)){
        if(suit == 'S') {
            if (rank < 7) spades.insert(spades.begin(),c);
            if (rank >= 7) spades.emplace_back(c);
        }
        if(suit == 'D') {
            if (rank < 7) diamonds.insert(diamonds.begin(),c);
            if (rank >= 7) diamonds.emplace_back(c);
        }
        if(suit == 'H') {
            if (rank < 7) hearts.insert(hearts.begin(),c);
            if (rank >= 7) hearts.emplace_back(c);
        }
        if(suit == 'C') {
            if (rank < 7) clubs.insert(clubs.begin(),c);
            if (rank >= 7) clubs.emplace_back(c);
        }
    }
}

void Game::shuffle(int seed, std::vector<std::shared_ptr<Player>> players) {
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 13; j++) {
			players[i]->dealCard(deck[i * 13 + j]);
		}
	}
}

int Game::first(std::vector<std::shared_ptr<Player>> p) {
	for (int i = 0; i < 4; i++) 
	{
		for (auto c:p[i]->getHandCard()) 
		{
			if (c.getRankNum() == 7 && c.getSuit() == 'S')
			{
				return i;
			}
		}
	}
	return -1;
}




bool Game::validity(Card c) {
	char suit = c.getSuit();
	int rank = c.getRankNum(); 

	if (spades.empty() && (suit != 'S' || rank != 7))
	{
		return false;
	}

	if (suit == 'C'){
		if(!clubs.empty() && rank == clubs[0].getRankNum()-1) return true;
		if(!clubs.empty() && rank == clubs[clubs.size()-1].getRankNum()+1) return true;
		if(clubs.empty() && rank == 7) return true;
	}

	if (suit == 'D') {
		if(!diamonds.empty() && rank == diamonds[0].getRankNum()-1) return true;
		if(!diamonds.empty() && rank == diamonds[diamonds.size()-1].getRankNum()+1) return true;
		if(diamonds.empty() && rank == 7) return true;
	}

	if (suit == 'H') {
		if(!hearts.empty() && rank == hearts[0].getRankNum()-1) return true;
		if(!hearts.empty() && rank == hearts[hearts.size()-1].getRankNum()+1) return true;
		if(hearts.empty() && rank == 7) return true;
	}

    if (suit == 'S') {
		if(!spades.empty() && rank == spades[0].getRankNum()-1) return true;
		if(!spades.empty() && rank == spades[spades.size()-1].getRankNum()+1) return true;
		if(spades.empty() && rank == 7) return true;
	}
	return false;
}



void Game::table(){
	std::cout << "Cards on the table:" << std::endl;
	std::cout << "Clubs:";
	for (auto c: clubs){
		std::cout << ' ' << c.getRank();
	}
	std::cout << std::endl;

	std::cout << "Diamonds:";
	for (auto c: diamonds) {
		std::cout << ' ' << c.getRank();
	}
	std::cout << std::endl;
	std::cout << "Hearts:";
	for (auto c: hearts) {
		std::cout << ' ' << c.getRank();
	}
	std::cout << std::endl;

	std::cout << "Spades:";
	for (auto c: spades) {
		std::cout << ' ' << c.getRank();
	}
	std::cout << std::endl;
}

void Game::getDeck(){
	for(int i = 0; i < 52; i++){
		std::cout << deck[i].getRank() << deck[i].getSuit();
		if((i + 1) % 13 == 0) {
			std::cout << std::endl;
        } else {
            std::cout << ' ';
        }
    }
}

bool Game::winner(std::vector<std::shared_ptr<Player>> p, std::vector<int>& g) {
	for (int i = 0; i < 4; i++){
	std::vector <Card> discard = p[i]->getDiscard();
	int gain = 0;
	for(auto c: discard){
		gain += c.getRankNum();
		g[i] = gain;
	}
	p[i]->addScore(gain);
	}

	for (int i = 0; i < 4; i++){
		if(p[i]->getScore()>=80) return true;
	}
	return false;
}

void Game::clearTable(){
	spades.clear();
	hearts.clear();
	clubs.clear();
	diamonds.clear();
}
