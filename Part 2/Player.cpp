#include "Player.h"
#include <map>
Player::Player() {}
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
    delete cannotAttack;

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
    toMove->clear(); //reset the toMove
    //Go through all territories bordering the player's
    for (Territory *t : *territories) {
        bool threat = false;
        for (int i = 0; i < t->getEdgeCount(); i++) {
            Territory *border = t->getEdges()[i];
            Player *owner = border->getOwner();
            //If the player doesn't own the bordering territory, and if player has less armies than it...
            if (owner != nullptr && owner != this && (border->getNumberOfArmies() > armies)) {
                out->push_back(t); //add the player's territory to the toDefend list
                threat = true;
                break;
            }
        }
        if (!threat) {
            toMove->push_back(t); //Otherwise, if the territory is not in danger, add it to the toMove list
        }
    }
    cout << "TERRITORIES TO DEFEND HAVE BEEN GENERATED FOR " << *this << endl;
    if (out->empty()) {
        return territories;
    }
    return out;
}

// Function that returns a list of territories corresponding to the Territories the player would like to attack
vector<Territory *> *Player::toAttack()
{
    auto *out = new vector<Territory *>;
    //Go through all the territories bordering the player's territories
    for (Territory *t : *territories) {
        for (int i = 0; i < t->getEdgeCount(); i++) {
            Territory *target = t->getEdges()[i];
            //If the player doesn't own a bordering territory,
            if (target->getOwner() != this) {
                    //add the player-owned territory
                    out->push_back(t);
                    //add the enemy or neutral-owned bordering territory
                    out->push_back(target);
            }
        }
    }
    cout << "TERRITORIES TO ATTACK HAVE BEEN GENERATED FOR " << *this << endl;
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
    Player *owner = t->getOwner();
    if (owner) {
        t->getOwner()->removeTerritory(t);
    }
    t->changeOwner(this);
    territoryCount++;
}

bool Player::removeTerritory(Territory *toRemove) {
    //Find the territory in the vector
    for (int i = 0; i < territories->size(); i++) {
        Territory *t = territories->at(i);
        if (t->getId() == toRemove->getId()) {
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
            //decrement territory count
            territoryCount--;
            return true;
        }
    }
    //if player does not have territory, return false
    return false;

}
void Player::addContinent(Continent *c) {
    //add continent to player, and player to continent
    Player *owner = c->getOwner();
    if (owner) {
        owner->removeContinent(c);
    }
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

OrdersList *Player::getOrdersList() {
    return orderList;
}

vector<Territory *> *Player::getToMove() {
    return toMove;
}

string *Player::getName() const {
    return name;
}

bool Player::isCardWon() const {
    return cardWon;
}

void Player::setCardWon(bool cardWon) {
    Player::cardWon = cardWon;
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









