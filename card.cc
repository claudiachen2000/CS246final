#include "card.h"

Card::Card(int n, char s): rank{n}, suit{s} {}

int Card::getRankNum() const {
	return rank;
}

char Card::getSuit() const {
	return suit;
}

char Card::getRank() const {
    if(rank == 1) return 'A';
    if(rank == 2) return '2';
    if(rank == 3) return '3';
    if(rank == 4) return '4';
    if(rank == 5) return '5';
    if(rank == 6) return '6';
    if(rank == 7) return '7';
    if(rank == 8) return '8';
    if(rank == 9) return '9';
    if(rank == 10) return 'T';
    if(rank == 11) return 'J';
    if(rank == 12) return 'Q';
    if(rank == 13) return 'K';
    return 'N';
}

bool operator==(const Card& c1,const Card& c2) {
    return c1.getSuit() == c2.getSuit() && c1.getRank() == c2.getRank();
}
