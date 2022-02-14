#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "../Part 1/Map.h"
using namespace std;

//BASE CLASS 
class order {
	public:
        //Constructors
        order(); 
        order(const order& other);
        order& operator=(const order& o);
        //Destructor
        virtual ~order();
        //Virtual validate and execute methods
        virtual bool validate() = 0;
        virtual void execute() = 0;
        //Static method
        static bool isBeside(Territory *t1, Territory *t2);
        //Accessors
        string * get_order_type() const;
        string * get_order_effect() const;
        Player * get_player() const;
        //Mutators
        void set_order_type(string order);
        void set_order_effect(string effect);
        void set_player(Player *player);
    private:
        friend ostream& operator<<(ostream&, const order&);
        string* order_type_;
        string* order_effect_;
        Player* player;
};

//SUBCLASSES - TYPES OF ORDERS 

class Deploy : public order {
    private:
        bool validate() override;
        Territory *territory;
        int numberOfArmies;
    public:
        //Constructors
        Deploy();
        Deploy(Player*,Territory*,int);
        Deploy(const Deploy& other);
        Deploy& operator=(const Deploy& o);
        //Destructor
        ~Deploy() override;
        //Getters
        Territory *getTerritory() const;
        int getNumberOfArmies() const;
        //Setters
        void setTerritory(Territory *territory);
        void setNumberOfArmies(int numberOfArmies);
        void execute() override;

};
class Advance : public order {
    private:
        Territory* start;
        Territory* target;
        int armies;
        bool validate() override;
    public:
        //Constructors
        Advance();
        Advance(Player*,Territory*, Territory*, int);
        Advance(const Advance& other);
        Advance& operator=(const Advance& other);
        void execute() override;
        //Destructor
        ~Advance() override;
        //Setters
        void setStart(Territory *start);
        void setTarget(Territory *target);
        void setArmies(int armies);
        //Getters
        Territory *getStart() const;
        Territory *getTarget() const;
        int getArmies() const;

};
class Bomb : public order {
    public:
        //Constructors
        Bomb();
        Bomb(Player*,Territory*,Territory*);
        Bomb(const Bomb& other);
        Bomb& operator=(const Bomb& o);
        //Destructor
        ~Bomb() override;
        //Getters
        Territory *getStart() const;
        Territory *getTarget() const;
        //Setters
        void setStart(Territory *start);
        void setTarget(Territory* target);
        void execute() override;
    private:
        Territory* start;
        Territory* target;
        bool validate() override;
};
class Blockade : public order {
    public:
        //Constructors
        Blockade();
        Blockade(Player*,Territory*);
        Blockade(const Blockade& other);
        Blockade& operator=(const Blockade& o);
        //Destructor
        ~Blockade() override;
        //Getters
        Territory *getTerritory() const;
        //Setters
        void setTerritory(Territory *territory);
        void execute() override;
    private:
        Territory* territory;
        bool validate() override;
};
class Airlift : public order {
    public:
        //Constructors
        Airlift();
        Airlift(Player*, Territory*,Territory*,int);
        Airlift(const Airlift& other);
        Airlift& operator=(const Airlift& o);
        //Destructor
        ~Airlift() override;
        //Getters
        Territory *getStart() const;
        Territory *getTarget() const;
        int getTroops() const;
        //Setters
        void setStart(Territory *start);
        void setTarget(Territory *target);
        void setTroops(int troops);
        void execute() override;
    private:
        Territory* start;
        Territory* target;
        int troops;
        bool validate() override;
};
class Negotiate : public order {
    public:
        //Constructors
        Negotiate();
        Negotiate(Player*,Player*);
        Negotiate(const Negotiate &other);
        Negotiate& operator=(const Negotiate& o);
        //Destructor
        ~Negotiate() override;
        void execute() override;
        //Getters
        Player *getPlayer2() const;
        //Setters
        void setPlayer2(Player *player2);
    private:
        Player* player2;
        bool validate() override;
};

//ORDERS LIST CLASS

class OrdersList{
public:
    OrdersList();
    OrdersList(const OrdersList &other);
    void add(order *o);
    bool move(order* o, int position);
    bool remove(order* o);
    bool contain(order *o);
    //Destructor
    ~OrdersList();

private:
    vector<order *> *list;
    vector<order *>::iterator *ptr;
};