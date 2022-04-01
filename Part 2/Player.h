#ifndef PLAYER_H
#define PLAYER_H
#include "../Part 1/Map.h"
#include "../Part 4/Cards.h"
#include "PlayerStrategy.h"
#include <vector>
#include <string>

class Hand;
class Deck;
class order;
class PlayerStrategy;

class Player {
	private:
        PlayerStrategy *strategy;
		std::string *name;
		OrdersList* orderList;
		Hand* hand;
        int armies;
        bool cardWon;
        vector<Territory *> *territories;
        vector<Continent *> *continents;
        vector<Territory *> *toMove;
        vector<Player *> *cannotAttack;
	public:
        Player();
        Player(std::string);
		Player &operator=(const Player &p);
		Player(Player &p);
		friend std::ostream& operator<< (std::ostream &out, const Player &p);
		~Player();
        bool issueOrder(order *o);
        void issueOrder();
        vector<Territory *> * toDefend(order *type);
        vector<Territory*> * toAttack(order *type);
        //Accessors
        vector<Territory *> * getTerritories();
        vector<Continent *> * getContinents();
        OrdersList *getOrdersList();
        Hand* getHand();
        int getArmies() const;
        string *getName() const;
        bool isCardWon() const;
        vector<Player *> *getCannotAttack() const;
        PlayerStrategy * getPlayerStrategy();

    //Mutators
        void addTerritory(Territory *t);
        bool removeTerritory(Territory *t);
        void addContinent(Continent *c);
        bool removeContinent(Continent *c);
        void setArmies(int armies);
        void setTerritories(vector<Territory *> *t);
        void setCannotAttack(vector<Player *> *cannotAttack);
        void clearCannotAttack();
        void setCardWon(bool cardWon);
        void setStrategy(PlayerStrategy *ps);


};

#endif