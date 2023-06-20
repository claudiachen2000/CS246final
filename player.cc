#include "player.h"

Player::Player(): score{0} {}

void Player::play(Card c){
	for(unsigned int i = 0; i < handcards.size(); i++) {
		if (handcards[i]==c){
			handcards.erase(handcards.begin() + i);
		}
	}
}

void Player::discard(Card c){
	for(unsigned int i = 0; i < handcards.size(); i++) {
        if (handcards[i]==c) {
            discards.emplace_back(handcards[i]);
            handcards.erase(handcards.begin() + i);
        }
    }
}

void Player::dealCard(Card c) {
	handcards.emplace_back(c);
}

std::vector<Card> Player::getHandCard() {
	return handcards;
}

std::vector<Card> Player::getValid() {
	return valid;
}

void Player::updateValid(std::vector<Card> c) {
	valid = c;
}

std::vector<Card> Player::getDiscard() {
	return discards;
}

int Player::getScore() {
	return score;
}

void Player::addScore(int n) {
	score += n;
}

void Player::clear() {
	discards.clear();
	valid.clear();
	handcards.clear();
	score = 0;
}

