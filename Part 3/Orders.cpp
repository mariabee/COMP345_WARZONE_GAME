#include <iostream>
#include <string>
#include <list> 
using namespace std;

class Order
{
public:
    virtual bool validate() = 0;
    virtual void execute() = 0;
    //Accessors
    string getOrderType() { return orderType; }
    string getOrderEffect() { return orderEffect; }
    //Mutators
    void setOrderType(string _o) { orderType = _o; }
    void setOrderEffect(string effect) { orderEffect = effect; }

private:
    friend ostream& operator<<(ostream&, const Order&);
    string orderType;
    string orderEffect;
};
ostream& operator << (ostream& strm, const Order& orderObj) {

    return strm << orderObj.orderType << endl;
}

//SUBCLASSES 

class Deploy : public Order {
public:
    //Default constructor 
    Deploy() { setOrderType("Deploy"); }

    void execute() {
        if (validate()) {
            setOrderEffect("Troops have been deployed.");
        }
    }
private:
    bool validate() {
        //PLACEHOLDER
        // if the territory blongs to the player
        return true;
    }
};
class Advance : public Order {
public:
    //Default constructor 
    Advance() { setOrderType("Advance"); }
    //add MapTerritory* and Player* to the param
    void execute() {
        if (validate()) {
            setOrderEffect("Troops have advanced.*");
            /*
            * If the map territory does not belong to the player
            * Then an attack happens with other player
            */
        }
    }
private:
    bool validate() {
        //PLACEHOLDER
        return true;
    }
};
class Bomb : public Order {
public:
    //Default constructor 
    Bomb() { setOrderType("Bomb"); }

    void execute() {
        if (validate()) {
            setOrderEffect("Territory has been bombed.*");

        }
    }
private:
    bool validate() {
        //PLACEHOLDER
        // if the target territory is adjacent to the player's territory
        return true;
        //else return false
    }
};
class Blockade : public Order {
public:
    //Default constructor 
    Blockade() { setOrderType("Blockade"); }

    void execute() {
        if (validate()) {
            setOrderEffect("Troops have tripled.\nThe territory is now neutral. *");

        }
    }
private:
    bool validate() {
        //PLACEHOLDER
        //if the territory belongs to the player
        return true;
        //else false
    }
};
class Airlift : public Order {
public:
    //Default constructor 
    Airlift() { setOrderType("Airlift"); }

    void execute() {
        if (validate()) {
            setOrderEffect("Troops have moved.*");
            //if the target territory does not belongs to the player
            //then an attack happens
        }
    }
private:
    bool validate() {
        //PLACEHOLDER
        return true;
    }
};
class Negotiate : public Order {
public:
    //Default constructor 
    Negotiate() { setOrderType("Negotiate"); }

    void execute() {
        if (validate()) {
            setOrderEffect("Attacks have been prevented until the end of turn.*");
        }
    }
private:
    bool validate() {
        //PLACEHOLDER
        return true;
    }
};

int main() {
    list<Order*> testList;
    Deploy* d = new Deploy();
    Advance* a = new Advance();
    Bomb* b = new Bomb();
    Blockade* bl = new Blockade();
    Airlift* ai = new Airlift();
    Negotiate* n = new Negotiate();
    testList.push_front(d);
    testList.push_front(a);
    testList.push_front(b);
    testList.push_front(bl);
    testList.push_front(ai);
    testList.push_front(n);


}