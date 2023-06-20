#ifndef __CARD_H_
#define __CARD_H_

class Card {
    int rank;
	char suit;

	public:
	Card(int n, char s);
	int getRankNum() const;
	char getSuit() const;
	char getRank() const;
};

bool operator==(const Card& c1,const Card& c2);

#endif
