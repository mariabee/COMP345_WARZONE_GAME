#ifndef PLAYER_H
#define PLAYER_H
#include "../Part 1/Map.h"
#include "../Part 3/Orders.h"
#include "../Part 4/Cards.h"
#include <vector>
#include <string>

class Hand;

class Player {
	private:
		std::string *name;
		OrdersList* orderList;
		vector<Territory *> *territories;
        vector<Continent *> *continents;
        vector<Territory *> *toMove;
		int territoryCount = 0;
		Hand* hand;
        int armies;

	public:
		Player(std::string);
		Player &operator=(const Player &p);
		Player(Player &p);
		friend std::ostream& operator<< (std::ostream &out, const Player &p);
		~Player();
		void setTerritories(vector<Territory *> *t, int count);
        void addTerritory(Territory *t);
        bool removeTerritory(Territory *t);
        void addContinent(Continent *c);
        bool removeContinent(Continent *c);
        void issueOrder(Deploy *d);
        void issueOrder(Advance *a);
        void issueOrder(Bomb *b);
        void issueOrder(Blockade *b);
        void issueOrder(Airlift *b);
        void issueOrder(Negotiate *b);
        vector<Territory *> * toDefend();
        vector<Territory*> * toAttack();
		void issueOrder(std::string);
		Hand* getHand();
        int getArmies() const;
        int getTerritoryCount() const;
        string *getName() const;
        vector<Territory *> * getTerritories();
        vector<Continent *> * getContinents();
        vector<Territory *> * getToMove();
        OrdersList *getOrdersList();
        void setArmies(int armies);


};

#endif