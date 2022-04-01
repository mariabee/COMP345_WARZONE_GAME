//
// Created by mpbur on 2022-03-30.
//

#ifndef GAMEENGINE_CPP_PLAYERSTRATEGY_H
#define GAMEENGINE_CPP_PLAYERSTRATEGY_H
#include "Orders.h"
#include "Map.h"

class Player;
class Deck;

class PlayerStrategy {
protected:
    static vector<Player *> *players;
    static Deck *deck;
public :
    virtual bool issueOrder(Player *p, order *o) = 0;
    virtual void issueOrder(Player *p) = 0;
    virtual vector<Territory *> * toDefend(Player *p, order *type) = 0;
    virtual vector<Territory *> * toAttack(Player *p, order *type) = 0;
    static void addDeck(Deck *d);
    static void addPlayers(vector<Player *> *p);
};

class HumanPlayerStrategy : public PlayerStrategy {
public :
    explicit HumanPlayerStrategy();
    bool issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    static Territory * toMove(Player *p);
    vector<Territory *> * toDefend(Player *, order *type) override;
    vector<Territory *> * toAttack(Player *p, order *type) override;
    static Player * generateNegotiate();
    static void displayToAdvance(Player *p);
    static void displayToAttack(Player *p);
    static void displayEnemyBorders(Territory *t, Player *p);
};
class AggressivePlayerStrategy : public PlayerStrategy {
public :
    explicit AggressivePlayerStrategy();
    bool issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    vector<Territory *> * toDefend(Player *p, order *type) override;
    vector<Territory *> * toAttack(Player *p, order *type) override;
};
class BenevolentPlayerStrategy : public PlayerStrategy {
public :
    BenevolentPlayerStrategy();
    bool issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    vector<Territory *> * toDefend(Player *p, order *type) override;
    vector<Territory *> * toAttack(Player *p, order *type ) override;
};
class NeutralPlayerStrategy : public PlayerStrategy {
public :
    NeutralPlayerStrategy();
    bool issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    vector<Territory *> * toDefend(Player *p, order *type) override;
    vector<Territory *> * toAttack(Player *p, order *type) override;
};
class CheaterPlayerStrategy : public PlayerStrategy {
public :
    CheaterPlayerStrategy();
    bool issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    vector<Territory *> * toDefend(Player *p, order *type) override;
    vector<Territory *> * toAttack(Player *p, order *type) override;
};



#endif //GAMEENGINE_CPP_PLAYERSTRATEGY_H
