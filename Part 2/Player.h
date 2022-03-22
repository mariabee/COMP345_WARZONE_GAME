#ifndef PLAYER_H
#define PLAYER_H
#include "../Part 1/Map.h"
#include "../Part 3/Orders.h"
#include "../Part 4/Cards.h"

#include <string>

class Hand;

class Player {
	private:
		std::string *name;
		OrdersList* orderList;
		Territory** territories;
		int territoryCount = 0;
		Hand* hand;
        int armies;

	public:
		Player(std::string);
		Player &operator=(const Player &p);
		Player(Player &p);
		friend std::ostream& operator<< (std::ostream &out, const Player &p);
		~Player();
		void setTerritories(Territory** t, int count);
        Territory** toDefend(int& c);
		Territory** toAttack(int& c);
		void issueOrder(std::string);
		Hand* getHand();
        int getArmies() const;
        void setArmies(int armies);
};

#endif