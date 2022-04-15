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
    static Player * generateNegotiate(Player *p);
    ~PlayerStrategy();
};

class HumanPlayerStrategy : public PlayerStrategy {
public :
    explicit HumanPlayerStrategy();
    HumanPlayerStrategy(const HumanPlayerStrategy &other);
    HumanPlayerStrategy& operator=(const OrdersList& other);
    bool issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    static Territory * toMove(Player *p);
    vector<Territory *> * toDefend(Player *, order *type) override;
    vector<Territory *> * toAttack(Player *p, order *type) override;
    static Player * generateNegotiate(Player *p);
    static void displayToAdvance(Player *p);
    static void displayToAttack(Player *p);
    static void displayEnemyBorders(Territory *t, Player *p);
    static void displayBorders(Territory *t, Player *p);

private:
    friend ostream& operator<<(ostream&, const HumanPlayerStrategy&);
};
class AggressivePlayerStrategy : public PlayerStrategy {
    Territory *previous;
public :
    explicit AggressivePlayerStrategy();
    AggressivePlayerStrategy(const AggressivePlayerStrategy &other);
    AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy& other);
    bool issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    vector<Territory *> * toDefend(Player *p, order *type) override;
    vector<Territory *> * toAttack(Player *p, order *type) override;
private:
    friend ostream& operator<<(ostream&, const AggressivePlayerStrategy&);
};
class BenevolentPlayerStrategy : public PlayerStrategy {
public :
    explicit BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy &other);
    BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy& other);
    bool issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    vector<Territory *> * toDefend(Player *p, order *type) override;
    vector<Territory *> * toAttack(Player *p, order *type ) override;
private:
    friend ostream& operator<<(ostream&, const BenevolentPlayerStrategy&);
};
class NeutralPlayerStrategy : public PlayerStrategy {
public :
    explicit NeutralPlayerStrategy();
    NeutralPlayerStrategy(const NeutralPlayerStrategy &other);
    NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& other);
    bool issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    vector<Territory *> * toDefend(Player *p, order *type) override;
    vector<Territory *> * toAttack(Player *p, order *type) override;
private:
    friend ostream& operator<<(ostream&, const NeutralPlayerStrategy&);
};
class CheaterPlayerStrategy : public PlayerStrategy {
public :
    explicit CheaterPlayerStrategy();
    CheaterPlayerStrategy(const CheaterPlayerStrategy &other);
    CheaterPlayerStrategy& operator=(const CheaterPlayerStrategy& other);
    bool issueOrder(Player *p, order *o) override;
    void issueOrder(Player *p) override;
    vector<Territory *> * toDefend(Player *p, order *type) override;
    vector<Territory *> * toAttack(Player *p, order *type) override;
private:
    friend ostream& operator<<(ostream&, const CheaterPlayerStrategy&);
};



#endif //GAMEENGINE_CPP_PLAYERSTRATEGY_H
