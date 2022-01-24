#pragma once
#include <string>
#include <iostream>
#include <string>
using namespace std;

//BASE CLASS 
class Order {
    public:
        virtual bool validate() = 0;
        virtual void execute() = 0; 
        //Accessors
        string getOrderType();
        string getOrderEffect();
        //Mutators
        void setOrderType(string _o);
        void setOrderEffect(string effect);

    private:
        friend ostream& operator<<(ostream&, const Order&);
        string orderType;
        string orderEffect;
};

//SUBCLASSES - TYPES OF ORDERS 

class Deploy : public Order {
    public:
        //Default constructor 
        Deploy();
        void execute();
    private:
        bool validate();
};
class Advance : public Order {
    public:
        //Default constructor 
        Advance();
        void execute();
    private:
        bool validate();
};
class Bomb : public Order {
    public:
        //Default constructor 
        Bomb();
        void execute();
    private:
        bool validate();
};
class Blockade : public Order {
    public:
        //Default constructor 
        Blockade(); 
        void execute();
    private:
        bool validate();
};
class Airlift : public Order {
    public:
        //Default constructor 
        Airlift();
        void execute();
    private:
        bool validate();
};
class Negotiate : public Order {
    public:
        Negotiate(); 
        void execute();
    private:
        bool validate();
};
