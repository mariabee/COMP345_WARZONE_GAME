#ifndef PLAYER_H
#define PLAYER_H
#include "../Part 1/Map.h"
#include "../Part 3/Orders.h"
#include "../Part 4/Cards.h"
#include <vector>
#include <string>

class Hand;
class Deck;

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
        bool cardWon;
        vector<Player *> *cannotAttack;

	public:
        Player();
		Player(std::string);
		Player &operator=(const Player &p);
		Player(Player &p);
		friend std::ostream& operator<< (std::ostream &out, const Player &p);
		~Player();

        void issueOrder(Deploy *d);
        void issueOrder(Advance *a);
        void issueOrder(Bomb *b);
        void issueOrder(Blockade *b);
        void issueOrder(Airlift *b);
        void issueOrder(Negotiate *b);
        void issueOrder(std::string);
        vector<Territory *> * toDefend();
        vector<Territory*> * toAttack();

        //Accessors
        vector<Territory *> * getTerritories();
        vector<Continent *> * getContinents();
        vector<Territory *> * getToMove();
        OrdersList *getOrdersList();
        Hand* getHand();
        int getArmies() const;
        int getTerritoryCount() const;
        string *getName() const;
        bool isCardWon() const;
        vector<Player *> *getCannotAttack() const;



    //Mutators
        void addTerritory(Territory *t);
        bool removeTerritory(Territory *t);
        void addContinent(Continent *c);
        bool removeContinent(Continent *c);
        void setArmies(int armies);
        void setTerritories(vector<Territory *> *t, int count);
        void setCannotAttack(vector<Player *> *cannotAttack);
        void setCardWon(bool cardWon);


};

#endif