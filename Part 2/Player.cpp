#include "Player.h"
#include <map>

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
}

// Assignment operator overload for Player
Player &Player::operator=(const Player &p)
{
	if (this == &p)
		return *this;
	delete name;
	delete hand;
	delete[] territories;
    delete[] continents;
    delete[] toMove;
	delete orderList;

	name = new string(*p.name);
	hand = new Hand(*p.hand);
	territoryCount = p.territoryCount;
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
	return *this;
}

// Copy constructor for Player
Player::Player(Player &p) {
    name = new string(*p.name);
    hand = new Hand(*p.hand);
    territoryCount = p.territoryCount;
    armies = p.getArmies();
    territories = new vector<Territory *>();
    continents = new vector<Continent *>();
    toMove = new vector<Territory *>();
    for (Territory *t: *p.getTerritories()) {
        territories->push_back(t);
    }
    for (Territory *t: *p.getToMove()) {
        territories->push_back(t);
    }
    orderList = new OrdersList(*p.getOrdersList());
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
vector<Territory *> *Player::toDefend()
{
    auto *out = new vector<Territory *>;
    toMove->clear();
    for (Territory *t : *territories) {
        bool threat = false;
        for (int i = 0; i < t->getEdgeCount(); i++) {
            Territory *border = t->getEdges()[i];
            if (border->getOwner() != this && border->getNumberOfArmies() > 0) {
                out->push_back(t);
                threat = true;
                break;
            }
        }
        if (!threat) {
            toMove->push_back(t);
        }
    }
    return out;
}

// Function that returns a list of territories corresponding to the Territories the player would like to attack
vector<Territory *> *Player::toAttack()
{
    auto *out = new vector<Territory *>;
    for (Territory *t : *territories) {
        for (int i = 0; i < t->getEdgeCount(); i++) {
            Territory *target = t->getEdges()[i];
            if (target->getOwner() != this) {
                    out->push_back(t);
                    out->push_back(target);
            }
        }
    }
    return out;
}

// Function that sets the Player's territories to a given list and count
void Player::setTerritories(vector<Territory *> *t, int count)
{
	territories = t;
    for (Territory *territory : *t) {
        territory->changeOwner(this);
    }
	territoryCount = count;
}

//ISSUE ORDERS
void Player::issueOrder(Deploy* d) {
    orderList->add(d);
    std::cout << "Player - Successfully issued order: DEPLOY \n ";
}
void Player::issueOrder(Advance* a) {
    orderList->add(a);
    std::cout << "Player - Successfully issued order: ADVANCE \n";
}
void Player::issueOrder(Bomb* b) {
    orderList->add(b);
    std::cout << "Player - Successfully issued order: BOMB \n";
}
void Player::issueOrder(Blockade* b) {
    orderList->add(b);
    std::cout << "Player - Successfully issued order: BLOCKADE \n";
}
void Player::issueOrder(Airlift* b) {
    orderList->add(b);
    std::cout << "Player - Successfully issued order: AIRLIFT \n";
}
void Player::issueOrder(Negotiate* b) {
    orderList->add(b);
    std::cout << "Player - Successfully issued order: DIPLOMACY \n";
}

// Function that creates an order based on the type passed as a string
void Player::issueOrder(std::string type)
{
	std::string typeMap[6] {"deploy", "advance", "bomb", "blockade", "airlift", "negotiate"};

	int index = -1;

	for(index = 0; index < 6; index++)
		if (type == typeMap[index]) break;

	order *o;
	switch (index)
	{
	case 0:
		o = new Deploy();
		break;
	case 1:
		o = new Advance();
		break;
	case 2:
		o = new Bomb();
		break;
	case 3:
		o = new Blockade();
		break;
	case 4:
		o = new Airlift();
		break;

	case 5:
		o = new Negotiate();
		break;
	default:
		std::cout << "Error::Player - Unknown Type: " << type << std::endl;
		return;
	}
}

int Player::getTerritoryCount() const {
    return territoryCount;
}

void Player::addTerritory(Territory *t) {
    territories->push_back(t);
    t->changeOwner(this);
    territoryCount++;
}

bool Player::removeTerritory(Territory *toRemove) {
    for (int i = 0; i < territories->size(); i++) {
        Territory *t = territories->at(i);
        if (t->getId() == toRemove->getId()) {
            t->changeOwner(nullptr);
            territories->erase(territories->begin() + i);
            Continent *c = t->getContinent();
            if (c->getOwner() == this) {
                removeContinent(c);
            }
            territoryCount--;
            return true;
        }
    }
    return false;

}
void Player::addContinent(Continent *c) {
    continents->push_back(c);
    c->setOwner(this);
}
bool Player::removeContinent(Continent *c) {
    for (int i = 0; i < continents->size(); i++) {
        if (continents->at(i)->getId() == c->getId()) {
            c->setOwner(nullptr);
            continents->erase(continents->begin() + i);
            return true;
        }
    }
    return false;
}

vector<Territory *> * Player::getTerritories() {
    return territories;
}

vector<Continent *> * Player::getContinents() {
    return continents;
}

OrdersList *Player::getOrdersList() {
    return orderList;
}

vector<Territory *> *Player::getToMove() {
    return toMove;
}

string *Player::getName() const {
    return name;
}





