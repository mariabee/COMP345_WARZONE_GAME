#include "Orders.h"
#include <list> 
// BASE CLASS

order::order()
{
    order_effect_ = nullptr;
    order_type_ = nullptr; 
}
//COPY CONSTRUCTOR
order::order(const order& other) 
{
    order_type_ = new string;
    order_effect_ = new string;
    *order_type_ = *other.order_type_;
    *order_effect_ = *other.order_effect_; 
}
//DESTRUCTOR 
order::~order()
{
    //delete order_effect_;
    //delete order_type_;
}

//ACCCESOR IMPLEMENTATION 
string order::get_order_type() const { return *order_type_; }
string order::get_order_effect() const { return *order_effect_; }
//MUTATOR IMPLEMENTATION 
void order::set_order_type(string order) { order_type_ = &order; }
void order::set_order_effect(string effect) { order_effect_ = &effect; }

//STREAM INSERTION OPERATOR IMPLEMENTATION 
ostream& operator << (ostream& stream, const order& order_obj) {

    return stream << "Order Type : " << order_obj.get_order_type() << endl
	<< "Order Effect : " << order_obj.get_order_effect() << endl; 
}


//SUBCLASS IMPLEMENTATION 

//DEPLOY
Deploy::Deploy()
{
	set_order_type("Deploy");
}
void Deploy::execute() {
    if (validate()) {
        set_order_effect("Troops have been deployed.");
    }
}
bool Deploy::validate() {
    //PLACEHOLDER
        // if the territory belongs to the player
    return true;
}

//ADVANCE
Advance::Advance() { set_order_type("Advance"); }
void Advance::execute() {
    if (validate()) {
        set_order_effect("Troops have advanced.*");
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
Bomb::Bomb() { set_order_type("Bomb"); }
void Bomb::execute() {
    if (validate()) {
        set_order_effect("Territory has been bombed.*");

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
Blockade::Blockade() { set_order_type("Blockade"); };
void Blockade::execute() {
    if (validate()) {
        set_order_effect("Troops have tripled.\nThe territory is now neutral. *");

       }
}
bool Blockade::validate() {
    //PLACEHOLDER
        //if the territory belongs to the player
    return true;
    //else false
}
//AIRLIFT 
Airlift::Airlift() { set_order_type("Airlift"); }
void Airlift::execute() {
    if (validate()) {
        set_order_effect("Troops have moved.*");
        //if the target territory does not belongs to the player
        //then an attack happens
    }
}
bool Airlift::validate() {
    //PLACEHOLDER
    return true;
}
//NEGOTIATE 
Negotiate::Negotiate() { set_order_type("Negotiate"); }
void Negotiate::execute() {
    if (validate()) {
        set_order_effect("Attacks have been prevented until the end of turn.*");
    }
}
bool Negotiate::validate() {
    //PLACEHOLDER
    return true;
}

