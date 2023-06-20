#include <iostream>
#include <sstream>
#include <chrono>
#include "player.h"
#include "human.h"
#include "computer.h"
#include "game.h"


int main(int argv, char ** argc) {
    int seed = 0;
    bool win = false;
    int round = 0;

    if(argv != 0) {
        std::stringstream ss;
        ss << argc[1];
        ss >> seed;
    } else {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }

    std::vector<int> gain = {0,0,0,0};
    std::vector<std::shared_ptr<Player>> players; 
	
    for (int i = 1; i <= 4; i++) {
		std::string choice = "";
		std::cout << "Is Player" << i << " a human (h) or a computer (c)?" << std::endl;
		std::cin >> choice;

		while (choice != "h" && choice != "c") {
			std::cout << "Please enter h or c." << std::endl;
			std::cout << "Is Player" << i << " a human (h) or a computer (c)?" << std::endl;
			std::cin >> choice;
		
		}

		if (choice == "h"){
			std::shared_ptr<Human> p = std::make_shared<Human>();
			players.emplace_back(p);
		}

		if(choice == "c") {
			std::shared_ptr<Computer> p = std::make_shared<Computer>();
			players.emplace_back(p);
		}
	}

    std::shared_ptr<Game> game = std::make_shared<Game>(); 
    game->shuffle(seed, players);
    int first = game->first(players);
    
    while(round < 52 && !win){
        if(players[(round+first)%4]->humanType()) {
            game->table();
            std::cout << "Your hand:";
            for (auto c: players[(round+first)%4]->getHandCard()) {
				std::cout << " " << c.getRank() << c.getSuit();
			}
            std::cout << std::endl;
            std::cout << "Legal plays:";
            std::vector<Card> valid;
            for (auto c: players[(round+first)%4]->getHandCard()) {
                if(game->validity(c)){
                    std::cout << " " << c.getRank() << c.getSuit();
                    valid.emplace_back(c);
                }
			}

            std::cout << std::endl;
            players[(round+first)%4]->updateValid(valid);
            bool error = true;
            while(error){
                std::string in;
                std::cin >> in;
                if(in == "play"){
                    std::string card;
                    std::cin >> card;
                    for(auto c:players[(round+first)%4]->getValid()){
                        if(c.getRank() == card[0] && c.getSuit() == card[1]){
                            std::cout << "Player" << (round+first)%4 + 1 << " plays " << card << "." << std::endl;
                            players[(round+first)%4]->play(c);
                            game->play(c);
                            error = false;
                            round++;
                            break;
                        }
                    }
                    if(error) std::cout << "This is not a legal play." << std::endl;
                } else if (in == "discard") {
                    std::string card;
                    std::cin >> card;
                    bool invalid = false;
                    if(!(players[(round+first)%4]->getValid().empty())){
                        std::cout << "You have a legal play. You may not discard." << std::endl;
                        error = true;
                        invalid = true;
                    }
                    if(!invalid){
                        bool found = false;
                        for(auto c:players[(round+first)%4]->getHandCard()){
                            if(c.getRank() == card[0] && c.getSuit() == card[1]){
                                std::cout << "Player" << (round+first)%4 + 1 << " discards " << card << "." << std::endl;
                                players[(round+first)%4]->discard(c);
                                error = false;
                                found = true;
                                round++;
                                break;
                            }
                        }
                        if(!found) {
                            std::cout << "You don't have this card." << std::endl;
                            error = true;
                        }
                    }
                } else if (in == "deck") {
                    game->getDeck();
                    error = true;
                } else if (in == "ragequit") {
                    std::cout << "Player" << (round+first)%4 + 1 << " ragequits. A computer will now take over." << std::endl; 
	                std::shared_ptr<Computer> comp = std::make_shared<Computer>();
                    comp->setHand(players[(round+first)%4]->getHandCard());
                    comp->setDiscard(players[(round+first)%4]->getDiscard());
                    comp->addScore(players[(round+first)%4]->getScore());
                    players[(round+first)%4] = comp;
                    error = false;
                } else if (in == "quit") {
                    return 0;
                } else {
                    std::cout << "This is not a legal command." << std::endl;
                    error = true;
                }
            }
        } else {
            std::vector<Card> valid;
            std::vector<Card> hand = players[(round+first)%4]->getHandCard();
            for (auto c: hand) {
                if(game->validity(c)){
                    valid.emplace_back(c);
                }
            }
            if(valid.empty()){
                players[(round+first)%4]->discard(hand[0]);
                std::cout << "Player" << (round+first)%4 + 1 << " discards " << hand[0].getRank() << hand[0].getSuit() << "." << std::endl;
                round++;
            } else {
                players[(round+first)%4]->play(valid[0]);
                game->play(valid[0]);
                std::cout << "Player" << (round+first)%4 + 1 << " plays " << valid[0].getRank() << valid[0].getSuit() << "." << std::endl;
                round++;
            }
        }
        if(round%4 == 0) win = game->winner(players, gain);
        if(!win && round == 52) {
            for(int i = 0; i < 4; i++){
                players[i]->clear();
            }
        game->shuffle(seed, players);
        game->clearTable();
        first = game->first(players);
        gain = {0,0,0,0};
        round = 0;
        }
    }

    if(win){
       int min = 1000;
       for(int i = 0; i < 4; i++) {
			std::cout << "Player" << i + 1 << "'s discards:";
			std::vector <Card> discard = players[i]->getDiscard();
			for(auto c: discard) {
				std::cout << " " << c.getRank() << c.getSuit(); 
			}
            std::cout << std::endl;
			std::cout << "Player" << i + 1 << "'s score: ";
            std::cout << players[i]->getScore() - gain[i] << " + " << gain[i] << " = " << players[i]->getScore() << std::endl;
            if(players[i]->getScore() < min) min = players[i]->getScore();
		}
        for(int i = 0; i < 4; i++) {
            if(min == players[i]->getScore()) std::cout << "Player" << i + 1 << " wins!" << std::endl;
        }
   }
}
