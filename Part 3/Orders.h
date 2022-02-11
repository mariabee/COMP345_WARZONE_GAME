#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//BASE CLASS 
class order {
	public:
        order(); 
        order(const order& other);
        order& operator=(const order& o);

        virtual ~order();
        virtual bool validate() = 0;
        virtual void execute() = 0; 
        //Accessors
        string * get_order_type() const;
        string * get_order_effect() const;
        //Mutators
        void set_order_type(const string &order);
        void set_order_effect(const string &effect);

    private:
        friend ostream& operator<<(ostream&, const order&);
        string* order_type_;
        string* order_effect_;
};

//SUBCLASSES - TYPES OF ORDERS 

class Deploy : public order {
    public:
        //Constructors
        Deploy();
        Deploy(const Deploy& other);
        Deploy& operator=(const Deploy& o);
        void execute() override;
    private:
        bool validate() override;
};
class Advance : public order {
    public:
        //Default constructor 
        Advance();
        Advance(const Advance& other);
        Advance& operator=(const Advance& other);
        void execute() override;
    private:
        bool validate() override;
};
class Bomb : public order {
    public:
        //Default constructor 
        Bomb();
        Bomb(const Bomb& other);
        Bomb& operator=(const Bomb& o);
    void execute() override;
    private:
        bool validate() override;
};
class Blockade : public order {
    public:
        //Default constructor 
        Blockade();
        Blockade(const Blockade& other);
        Blockade& operator=(const Blockade& o);
        void execute() override;
    private:
        bool validate() override;
};
class Airlift : public order {
    public:
        //Default constructor 
        Airlift();
        Airlift(const Airlift& other);
        Airlift& operator=(const Airlift& o);
        void execute() override;
    private:
        bool validate() override;
};
class Negotiate : public order {
    public:
        Negotiate();
        Negotiate(const Negotiate &other);
        Negotiate& operator=(const Negotiate& o);
        void execute() override;
    private:
        bool validate() override;
};

//ORDERS LIST CLASS

class OrdersList{
public:
    OrdersList();

    void add(order *o);
    bool move(order* o, int position);
    bool remove(order* o);
    bool contain(order *o);

    virtual ~OrdersList();

private:
    vector<order *> *list;
    vector<order *>::iterator *ptr;
};