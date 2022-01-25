#include "Orders.h"
#include <bits/stdc++.h>

// BASE CLASS IMPLEMENTATION
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
    delete order_effect_;
    delete order_type_;
}

//ACCESSOR IMPLEMENTATION
string order::get_order_type() const {
    if (order_type_) {
        return *order_type_;
    }
    return ""; }
string order::get_order_effect() const {
    if (order_effect_) {
        return *order_effect_;
    }
    return ""; }
//MUTATOR IMPLEMENTATION 
void order::set_order_type(const string &order) { order_type_ = new string(order); }
void order::set_order_effect(const string &effect) { order_effect_ = new string(effect); }

//STREAM INSERTION OPERATOR IMPLEMENTATION 
ostream& operator << (ostream& stream, const order& order_obj) {
    string description_ = "Order Type : " + order_obj.get_order_type() + "\n";
    if (order_obj.get_order_effect().empty()) {
        description_ += "Order Effect : " + order_obj.get_order_effect() + "\n";
    }
    return stream << description_;
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
Blockade::Blockade() { set_order_type("Blockade"); }
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
        //if the target territory does not belong to the player
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
//ORDERS LIST IMPLEMENTATION

void OrdersList::add(order* o) {
    list.push_back(o);
}
void OrdersList::move(order* o, int position) {
    auto it = list.begin()+position;
    if(contain(&o)) {
        remove(o);
        list.insert(it, o);
    }
    else{
        cout<<"Order not found";
        return;
    }
}

void OrdersList::remove(order* o) {
    ptr = find(list.begin(), list.end(),o);
    list.erase(ptr);
}

bool OrdersList::contain(order **o) {
    ptr = find(list.begin(), list.end(),*o);
    if (ptr != list.end())
    {
        //WE SHOULD MAKE AN ORDER PRINT FUNCTION FOR DEBUGGING AFTER MAP AND PLAYER
        cout << "Element " << o <<" found at position : " ;
        cout << ptr - list.begin() <<endl;
        ptr = list.begin();
        return true;
    }
    else {
        std::cout << "Element not found.\n\n";
        ptr = list.begin();
        return false;
    }
}

OrdersList::OrdersList(){
    list;
    ptr;
}

OrdersList::~OrdersList() {
    list.clear();
}