#include "Orders.h"
#include <list> 


//ACCCESOR IMPLEMENTATION 
string Order::getOrderType() { return orderType;; };
string Order::getOrderEffect() { return orderEffect; };
//MUTATOR IMPLEMENTATION 
void Order::setOrderType(string order) { orderType = order; };
void Order::setOrderEffect(string effect) { orderEffect = effect; };

//STREAM INSERTION OPERATOR IMPLEMENTATION 
ostream& operator << (ostream& strm, const Order& orderObj) {

    return strm << orderObj.orderType << endl;
}

//SUBCLASS IMPLEMENTATION 

//DEPLOY
Deploy::Deploy() { setOrderType("Deploy"); }
void Deploy::execute() {
    if (validate()) {
        setOrderEffect("Troops have been deployed.");
    }
}
bool Deploy::validate() {
    //PLACEHOLDER
        // if the territory blongs to the player
    return true;
}

//ADVANCE
Advance::Advance() { setOrderType("Advance"); }
void Advance::execute() {
    if (validate()) {
        setOrderEffect("Troops have advanced.*");
        /*
        * If the map territory does not belong to the player
        * Then an attack happens with other player
        */
    }
}
bool Advance::validate() {
    return true; 
}

//BOMB 
Bomb::Bomb() { setOrderType("Bomb"); }
void Bomb::execute() {
    if (validate()) {
        setOrderEffect("Territory has been bombed.*");

    }
}
bool Bomb::validate() {
    {
        //PLACEHOLDER
        // if the target territory is adjacent to the player's territory
        return true;
        //else return false
    }
}
//BLOCKADE
Blockade::Blockade() { setOrderType("Blockade"); };
void Blockade::execute() {
    if (validate()) {
            setOrderEffect("Troops have tripled.\nThe territory is now neutral. *");

       }
}
bool Blockade::validate() {
    //PLACEHOLDER
        //if the territory belongs to the player
    return true;
    //else false
}
//AIRLIFT 
Airlift::Airlift() { setOrderType("Airlift"); }
void Airlift::execute() {
    if (validate()) {
        setOrderEffect("Troops have moved.*");
        //if the target territory does not belongs to the player
        //then an attack happens
    }
}
bool Airlift::validate() {
    //PLACEHOLDER
    return true;
}
//NEGOTIATE 
Negotiate::Negotiate() { setOrderType("Negotiate"); }
void Negotiate::execute() {
    if (validate()) {
        setOrderEffect("Attacks have been prevented until the end of turn.*");
    }
}
bool Negotiate::validate() {
    //PLACEHOLDER
    return true;
}

//TEMPORARY MAIN METHOD FOR TESTING 
int main() {
    cout << "THIS WORKS"; 
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