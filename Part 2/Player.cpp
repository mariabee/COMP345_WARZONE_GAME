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
    armies =3;
}

// Assignment operator overload for Player
Player &Player::operator=(const Player &p)
{
	if (this == &p)
		return *this;
	delete name;
	delete hand;
	delete[] territories;
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
Player::Player(Player &p)
{
	name = new string(*p.name);
	hand = new Hand(*p.hand);
	territoryCount = p.territoryCount;
	territories = new vector<Territory *>();
	for (int i = 0; i < territoryCount; i++)
	{
		territories[i] = p.territories[i];
	}
	orderList = new OrdersList(*p.orderList);
    armies = p.armies;
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
Territory **Player::toDefend(int &defendCount)
{
	Territory **out;

	defendCount = (territoryCount / 2);

	out = new Territory *[defendCount];

	int index = 0;
	for (int i = 0; i < territoryCount; i++)
		if (i % 2 == 1)
			out[index++] = territories->at(i);
	return out;
}

// Function that returns a list of territories corresponding to the Territories the player would like to attack
Territory **Player::toAttack(int &attackCount)
{
	Territory **out;

	attackCount = (territoryCount / 2) + 1;

	out = new Territory *[attackCount];

	int index = 0;
	for (int i = 0; i < territoryCount; i++)
		if (i % 2 == 0)
			out[index++] = territories->at(i);

	return out;
}

// Function that sets the Player's territories to a given list and count
void Player::setTerritories(vector<Territory *> *t, int count)
{
	territories = t;
	territoryCount = count;
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

	std::cout << "Player - Successfully issued order: " << type << std::endl;
	orderList->add(o);
}

int Player::getTerritoryCount() const {
    return territoryCount;
}

void Player::addTerritory(Territory *t) {
    territories->push_back(t);
    territoryCount++;
}

bool Player::removeTerritory(Territory *toRemove) {
    for (int i = 0; i < territories->size(); i++) {
        Territory *t = territories->at(i);
        if (t->getId() == toRemove->getId()) {
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





