#include "Player.h"
#include <map>
//Default constructor
Player::Player() {

}
// Constructor for Player
Player::Player(std::string n)
{
	name = new string(move(n));
	orderList = new OrdersList();
	hand = new Hand();
    territories = new vector<Territory *>();
    continents = new vector<Continent *>();
    toMove = new vector<Territory *>();
    armies = 3;
    cardWon= false;
    cannotAttack = new vector<Player *>();
    strategy = nullptr;
}

// Assignment operator overload for Player
Player &Player::operator=(const Player &p)
{
	if (this == &p)
		return *this;
	delete name;
    delete strategy;
	delete hand;
	delete[] territories;
    delete[] continents;
    delete[] toMove;
	delete orderList;

	name = new string(*p.name);
	hand = new Hand(*p.hand);
	territories = new vector<Territory *>();
    continents = new vector<Continent *>();
	for (Territory *t : *p.territories )
	{
		territories->push_back(t);
	}
    for (Continent *c : *p.continents) {
        continents->push_back(c);
    }
	orderList = new OrdersList(*p.orderList);
    cannotAttack = new vector<Player *>();
    for (Player* p: *p.cannotAttack)
    {
        cannotAttack->push_back(p);
    }
	return *this;
}

// Copy constructor for Player
Player::Player(Player &p) {
    name = new string(*p.name);
    hand = new Hand(*p.hand);
    armies = p.getArmies();
    territories = new vector<Territory *>();
    continents = new vector<Continent *>();
    toMove = new vector<Territory *>();
    for (Territory *t: *p.getTerritories()) {
        territories->push_back(t);
    }
    orderList = new OrdersList(*p.getOrdersList());
    cardWon = p.cardWon;
    cannotAttack = new vector<Player *>();
    for (Player* p: *p.cannotAttack)
    {
        cannotAttack->push_back(p);
    }
}

// Stream insertion operator overload for Player
std::ostream &operator<<(std::ostream &out, const Player &p)
{
    out << *p.name;
	return out;
}

// Destructor for Player
Player::~Player()
{
	delete name;
	delete hand;
	delete orderList;

	// Delete only the array of pointers since the territories should be deleted from the map not the player
	delete[] territories;
    delete[] continents;
    delete[] toMove;
    delete[] cannotAttack;

}

// Function that returns a pointer to the players hand
Hand *Player::getHand()
{
	return hand;
}

int Player::getArmies() const {
    return armies;
}
void Player::setArmies(int armies) {
    Player::armies = armies;
}
// Function that returns a list of territories corresponding to the Territories the player would like to defend
vector<Territory *> *Player::toDefend(order *type)
{
    return strategy->toDefend(this, type);
}

// Function that returns a list of territories corresponding to the Territories the player would like to attack
vector<Territory *> *Player::toAttack(order *type)
{
    return strategy->toAttack(this, type);
}

// Function that sets the Player's territories to a given list and count
void Player::setTerritories(vector<Territory *> *t)
{
	territories = t;
    for (Territory *territory : *t) {
        territory->changeOwner(this);
    }
}



void Player::addTerritory(Territory *t) {
    Player *owner = t->getOwner(); //get the territory owner
    if (owner) { //if the territory has an owner...
        if (owner != this) { //if the owner isn't the player,
            t->getOwner()->removeTerritory(t); //remove the territory from its current owner
            territories->push_back(t); //add the territory to player
            t->changeOwner(this); //add the player to territory
        }
    }
    else {
        t->changeOwner(this);
        territories->push_back(t);
    }
}

bool Player::removeTerritory(Territory *toRemove) {
    //Find the territory in the vector
    for (int i = 0; i < territories->size(); i++) {
        Territory *t = territories->at(i);
        if (t == toRemove) {
            //change the owner in Territory
            t->changeOwner(nullptr);
            //erase the territory in Player
            territories->erase(territories->begin() + i);
            //Check if the continent of the territory was owned by Player
            Continent *c = t->getContinent();
            //if so, remove continent
            if (c->getOwner() == this) {
                removeContinent(c);
            }
            return true;
        }
    }
    //if player does not have territory, return false
    return false;

}
void Player::addContinent(Continent *c) {
    //add continent to player, and player to continent
    continents->push_back(c);
    c->setOwner(this);
}
bool Player::removeContinent(Continent *c) {
    //find the continent in the player's vector
    for (int i = 0; i < continents->size(); i++) {
        if (continents->at(i)->getId() == c->getId()) {
            //remove player from continent
            c->setOwner(nullptr);
            //remove continent from player
            continents->erase(continents->begin() + i);
            return true;
        }
    }
    //return false if player did not own continent
    return false;
}

vector<Territory *> * Player::getTerritories() {
    return territories;
}

vector<Continent *> * Player::getContinents() {
    return continents;
}
PlayerStrategy *Player::getPlayerStrategy() {
    return strategy;
}

OrdersList *Player::getOrdersList() {
    return orderList;
}


string *Player::getName() const {
    return name;
}

bool Player::isCardWon() const {
    return cardWon;
}

void Player::setCardWon(bool won) {
    Player::cardWon = won;
}

vector<Player *> *Player::getCannotAttack() const {
    return cannotAttack;
}

void Player::setCannotAttack(vector<Player *> *cannotAttack) {
    Player::cannotAttack = cannotAttack;
}

void Player::clearCannotAttack() {
    cannotAttack->clear();
}

void Player::setStrategy(PlayerStrategy *ps) {
    strategy = ps;
}

bool Player::issueOrder(order *o) {
    if (!territories->empty()) {
        return strategy->issueOrder(this, o);
    }
    return false;
}

void Player::issueOrder() {
    if (!territories->empty()) {
        strategy->issueOrder(this);
    }
}











