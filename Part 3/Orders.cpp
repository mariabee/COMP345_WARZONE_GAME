#include "Orders.h"
#include <bits/stdc++.h>

// BASE CLASS IMPLEMENTATION
order::order()
{
    order_effect_ = new string();
    order_type_ = new string();
}
//COPY CONSTRUCTOR
order::order(const order& other) 
{
    order_type_ = new string(*other.order_type_);
    order_effect_ = new string(*other.order_effect_);
}
bool order::isBeside(Territory *src, Territory *target) {
    for (int i = 0; i < src->getEdgeCount(); i++) {
        if (src->getEdges()[i] == target) {
            return true;
        }
    }
    return false;
}
// = OPERATOR
order &order::operator=(const order &o) {
    if (this == &o) return *this;
    delete order_effect_;
    delete order_type_;
    order_effect_ = new string(*o.order_effect_);
    order_type_ = new string(*o.order_type_);
    return *this;
}
//DESTRUCTOR 
order::~order()
{
    delete order_effect_;
    delete order_type_;
    order_effect_ = nullptr;
    order_type_ = nullptr;
}

//ACCESSOR IMPLEMENTATION
string *order::get_order_type() const {
        return order_type_;
}
string *order::get_order_effect() const {
        return order_effect_;
}
//MUTATOR IMPLEMENTATION 
void order::set_order_type(const string &order) { order_type_ = new string(order); }
void order::set_order_effect(const string &effect) { order_effect_ = new string(effect); }

//STREAM INSERTION OPERATOR IMPLEMENTATION 
ostream& operator << (ostream& stream, const order& order_obj) {
    string description_ = "Order Type : " + *order_obj.get_order_type() + "\n";
    if (!order_obj.get_order_effect()->empty()) {
        description_ += "Order Effect : " + *order_obj.get_order_effect() + "\n";
    }
    return stream << description_;
}

//SUBCLASS IMPLEMENTATION 

//DEPLOY
Deploy::Deploy()
{
	set_order_type("Deploy");
}
Deploy::Deploy(const Deploy &other) : order(other) {}
Deploy &Deploy::operator=(const Deploy &o)  {
    order::operator = (o);
    return *this;
}
void Deploy::execute() {
    if (validate()) {
        set_order_effect("Troops have been deployed.");
        cout << *get_order_effect() << endl;
    }
}
bool Deploy::validate() {
    //PLACEHOLDER
        // if the territory belongs to the player
    return true;
}

//ADVANCE
Advance::Advance() { set_order_type("Advance"); }
Advance::Advance(const Advance &other) : order(other) {}
Advance&Advance::operator=(const Advance &o)  {
    order::operator = (o);
    return *this;
}
void Advance::execute() {
    if (validate()) {
        set_order_effect("Troops have advanced.*");
        cout << *get_order_effect() << endl;
    }
}
bool Advance::validate() {
    /*
        * If the map territory does not belong to the player
        * Then an attack happens with other player
        */
    return true; 
}

//BOMB
//CONSTRUCTORS
Bomb::Bomb() { set_order_type("Bomb"); }
Bomb::Bomb(const Bomb &other) : order(other){}
Bomb &Bomb::operator=(const Bomb &o) {
    order::operator = (o);
    return *this;
}
void Bomb::execute() {
    if (validate()) {
        set_order_effect("Territory has been bombed.*");
        cout << *get_order_effect() << endl;
    }
}
bool Bomb::validate() {
    {
        //PLACEHOLDER
        // if the target territory is adjacent to the player's territory
        return true;
        //else return false
    }}
//BLOCKADE
Blockade::Blockade() { set_order_type("Blockade"); }
Blockade::Blockade(const Blockade &other) : order(other) {}
Blockade &Blockade::operator=(const Blockade &o) {
    order::operator = (o);
    return *this;
}
void Blockade::execute() {
    if (validate()) {
        set_order_effect("Troops have tripled.\nThe territory is now neutral. ");
        cout << *get_order_effect() << endl;
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
Airlift::Airlift(const Airlift &other) : order(other) {}
Airlift &Airlift::operator=(const Airlift &o) {
    order::operator = (o);
    return *this;
}
void Airlift::execute() {
    if (validate()) {
        set_order_effect("Troops have moved.");
        cout << *get_order_effect() << endl;
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
Negotiate::Negotiate(const Negotiate &other) : order(other) {}
Negotiate &Negotiate::operator=(const Negotiate &o) {
    order::operator = (o);
    return *this;
}
void Negotiate::execute() {
    if (validate()) {
        set_order_effect("Attacks have been prevented until the end of turn.");
        cout << *get_order_effect() << endl;
    }
}
bool Negotiate::validate() {
    //PLACEHOLDER
    return true;
}

//ORDERS LIST IMPLEMENTATION

void OrdersList::add(order* o) {
    list->push_back(o);
}
bool OrdersList::move(order* o, int position) {
    if (position >= list->size()) {
        cout << "Position is out of range. " << endl;
        return false;
    }
    auto it = list->begin()+position;
    if(contain(o)) {
        remove(o);
        list->insert(it, o);
        cout << *o->get_order_type() << " moved to position " << position << "." << endl;
        return true;
    }
    cout<<"Order not found";
    return false;
}

bool OrdersList::remove(order* o) {
    *ptr = find(list->begin(), list->end(),o);
    if (*ptr != list->end()) {
        list->erase(*ptr);
        cout << *o->get_order_type() << " successfully removed. " << endl;
        return true;
    }
    return false;
}
bool OrdersList::contain(order *o) {
    *ptr = find(list->begin(), list->end(), o);
    if (*ptr != list->end())
    {
        cout << *o->get_order_type() + " found  at position : " ;
        cout << *ptr - list->begin() <<endl;
        *ptr = list->begin();
        return true;
    }
    else {
        std::cout << "Element not found.\n\n";
        *ptr = list->begin();
        return false;
    }
}

OrdersList::OrdersList(){
    list = new vector<order *>();
    ptr = new vector<order *>::iterator();
}

OrdersList::~OrdersList() {
    //CURRENTLY, DESTRUCTOR DELETES THE POINTERS, BUT NOT THE ORDER OBJECTS THEY POINT TO.
    list->clear();
    delete list;
    delete ptr;
    list = nullptr;
    ptr = nullptr;
}



