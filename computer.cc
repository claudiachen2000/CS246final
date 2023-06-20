#include "computer.h"

Computer::Computer(): Player{} {}

void Computer::setDiscard(std::vector<Card> dis){
    discards = dis;
}

void Computer::setHand(std::vector<Card> hand){
    handcards = hand;
}

bool Computer::humanType() {
    return false;
}
