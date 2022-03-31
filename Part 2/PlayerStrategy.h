//
// Created by mpbur on 2022-03-30.
//

#ifndef GAMEENGINE_CPP_PLAYERSTRATEGY_H
#define GAMEENGINE_CPP_PLAYERSTRATEGY_H


#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"

class PlayerStrategy {
public :
    static vector<Player> *players;
    static Deck *deck;
    virtual void issueOrder(Player *p, order *o) = 0;
    virtual void issueOrder(Player *p) = 0;
    virtual vector<Territory *> * toDefend(Player *p) = 0;
    virtual vector<Territory *> * toAttack(Player *p) = 0;
    virtual Territory * toMove(Player *p) = 0;
};

class HumanPlayerStrategy : public PlayerStrategy {
public :
    explicit HumanPlayerStrategy();
    void issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    Territory * toMove(Player *p) override;
    vector<Territory *> * toDefend(Player *p) override;
    vector<Territory *> * toAttack(Player *p) override;
};
class AggressivePlayerStrategy : public PlayerStrategy {
public :
    explicit AggressivePlayerStrategy();
    void issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    Territory * toMove(Player *p) override;
    vector<Territory *> * toDefend(Player *p) override;
    vector<Territory *> * toAttack(Player *p) override;
};
class BenevolentPlayerStrategy : public PlayerStrategy {
public :
    BenevolentPlayerStrategy();
    void issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    Territory * toMove(Player *p) override;
    vector<Territory *> * toDefend(Player *p) override;
    vector<Territory *> * toAttack(Player *p) override;
};
class NeutralPlayerStrategy : public PlayerStrategy {
public :
    NeutralPlayerStrategy();
    void issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    Territory * toMove(Player *p) override;
    vector<Territory *> * toDefend(Player *p) override;
    vector<Territory *> * toAttack(Player *p) override;
};
class CheaterPlayerStrategy : public PlayerStrategy {
public :
    CheaterPlayerStrategy();
    void issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    Territory * toMove(Player *p) override;
    vector<Territory *> * toDefend(Player *p) override;
    vector<Territory *> * toAttack(Player *p) override;
};



#endif //GAMEENGINE_CPP_PLAYERSTRATEGY_H
