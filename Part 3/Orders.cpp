#include "Orders.h"
#include <bits/stdc++.h>

// BASE CLASS IMPLEMENTATION
#pragma region Order
//DEFAULT CONSTRUCTOR
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

//CHECK IS 2 TERRITORIES ARE ADJACENT
bool order::isBeside(Territory *src, Territory *target) {
    for (int i = 0; i < src->getEdgeCount(); i++) {
        if (src->getEdges()[i] == target) {
            return true;
        }
    }
    return false;
}
#pragma endregion Order

//SUBCLASS IMPLEMENTATION 
#pragma region Deploy
//DEPLOY
//DEFAULT CONSTRUCTOR
Deploy::Deploy()
{
    player = nullptr;
    territory = nullptr;
    numberOfArmies = 0;
	set_order_type("Deploy");
}
//CONSTRUCTOR
Deploy::Deploy(Player *p, Territory *t, int nbr) {
    this->player=p;
    this->territory=t;
    this->numberOfArmies=nbr;
    set_order_type("Deploy");
}
//COPY CONSTRUCTOR
Deploy::Deploy(const Deploy &other) : order(other) {
    this->player = other.getPlayer();
    this->numberOfArmies = other.getNumberOfArmies();
    this->territory = other.getTerritory();
    set_order_type("Deploy");
}
// = OPERATOR
Deploy &Deploy::operator=(const Deploy &o)  {
    order::operator = (o);
    return *this;
}
//EXECUTE
void Deploy::execute() {
    if (validate()) {
        set_order_effect("Troops have been deployed.");
        cout << *get_order_effect() << endl;
    }
}
//VALIDATE
bool Deploy::validate() {
    if(territory->getOwner() !=player){
        return false;
    }else
        return true;
}
//GETTERS
Player *Deploy::getPlayer() const {
    return player;
}
Territory *Deploy::getTerritory() const {
    return territory;
}
int Deploy::getNumberOfArmies() const {
    return numberOfArmies;
}
//SETTERS
void Deploy::setPlayer(Player *player) {
    Deploy::player = player;
}
void Deploy::setTerritory(Territory *territory) {
    Deploy::territory = territory;
}
void Deploy::setNumberOfArmies(int numberOfArmies) {
    Deploy::numberOfArmies = numberOfArmies;
}
//DESTRUCTOR
Deploy::~Deploy() {
    player= nullptr;
    territory= nullptr;
}

#pragma endregion Deploy

#pragma region Advance
//ADVANCE
//DEFAULT CONSTRUCTOR
Advance::Advance() {
    player = nullptr;
    start = nullptr;
    target = nullptr;
    armies = 0;
    set_order_type("Advance");
}
//CONSTRUCTOR
Advance::Advance(Player* player,Territory* start, Territory* target, int armies) {
    this->player=player;
    this->start=start;
    this->target=target;
    this->armies=armies;
    set_order_type("Advance");
}
//COPY CONSTRUCTOR
Advance::Advance(const Advance &other) : order(other) {
    this->player = other.getPlayer();
    this->start = other.getStart();
    this->target = other.getTarget();
    this->armies = other.getArmies();
    set_order_type("Advance");
}
// = OPERATOR
Advance&Advance::operator=(const Advance &o)  {
    order::operator = (o);
    return *this;
}
//EXECUTE
void Advance::execute() {
    if (validate()) {
        set_order_effect("Troops have advanced.*");
        cout << *get_order_effect() << endl;
    }
}
//VALIDATE
bool Advance::validate() {
    if(start->getOwner() != player || !isBeside(start,target) || start->getNumberOfArmies() < armies){
        return false;
    }else
        return true;
}
//SETTERS
void Advance::setPlayer(Player *player) {
    Advance::player = player;
}
void Advance::setStart(Territory *start) {
    Advance::start = start;
}
void Advance::setTarget(Territory *target) {
    Advance::target = target;
}
void Advance::setArmies(int armies) {
    Advance::armies = armies;
}
//GETTERS
Player *Advance::getPlayer() const {
    return player;
}
Territory *Advance::getStart() const {
    return start;
}
Territory *Advance::getTarget() const {
    return target;
}
int Advance::getArmies() const {
    return armies;
}
//DESTRUCTOR
Advance::~Advance() {
    player= nullptr;
    start= nullptr;
    target= nullptr;
}
#pragma endregion Advance

#pragma region Bomb
//BOMB
//DEFAULT CONSTRUCTOR
Bomb::Bomb() { set_order_type("Bomb"); }
//CONSTRUCTOR
Bomb::Bomb(Player* player, Territory* start, Territory* target) {
    this->player=player;
    this->start=start;
    this->target=target;
    set_order_type("Bomb");
}
//COPY CONSTRUCTOR
Bomb::Bomb(const Bomb &other) : order(other){
    this->player= other.getPlayer();
    this->start=other.getStart();
    this->target=other.getTarget();
    set_order_type("Bomb");
}
// = OPERATOR
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
    if(start->getOwner() != player || target->getOwner() == player || !isBeside(start,target)){
        return false;
    }else
        return true;
}
//GETTERS
Player *Bomb::getPlayer() const {
    return player;
}
Territory *Bomb::getStart() const {
    return start;
}
Territory *Bomb::getTarget() const {
    return target;
}
//SETTERS
void Bomb::setPlayer(Player *player) {
    Bomb::player = player;
}
void Bomb::setStart(Territory *start) {
    Bomb::start = start;
}
void Bomb::setTarget(Territory* target){
    Bomb::target = target;
}
//DESTRUCTOR
Bomb::~Bomb(){
    player= nullptr;
    start= nullptr;
    target= nullptr;
}
#pragma endregion Bomb

#pragma region Blockade
//BLOCKADE
//DEFAULT CONSTRUCTOR
Blockade::Blockade() { set_order_type("Blockade"); }
//CONSTRUCTOR
Blockade::Blockade(Player* player, Territory* territory) {
    this->player=player;
    this->territory=territory;
    set_order_type("Blockade");
}
//COPY CONSTRUCTOR
Blockade::Blockade(const Blockade &other) : order(other) {
    this->player=other.getPlayer();
    this->territory=other.getTerritory();
    set_order_type("Blockade");
}
// = OPERATOR
Blockade &Blockade::operator=(const Blockade &o) {
    order::operator = (o);
    return *this;
}
//EXECUTE
void Blockade::execute() {
    if (validate()) {
        set_order_effect("Troops have tripled.\nThe territory is now neutral. ");
        cout << *get_order_effect() << endl;
    }
}
//VALIDATE
bool Blockade::validate() {
    if(territory->getOwner() !=player){
        return false;
    }else
        return true;
}
//GETTERS
Player *Blockade::getPlayer() const {
    return player;
}
Territory *Blockade::getTerritory() const {
    return territory;
}
//SETTERS
void Blockade::setPlayer(Player *player) {
    Blockade::player = player;
}
void Blockade::setTerritory(Territory *territory) {
    Blockade::territory = territory;
}
//DESTRUCTOR
Blockade::~Blockade() {
    player = nullptr;
    territory = nullptr;
}
#pragma endregion Blockade

#pragma region Airlift
//AIRLIFT
//DEFAULT CONSTRUCTOR
Airlift::Airlift() { set_order_type("Airlift"); }
//CONSTRUCTOR
Airlift::Airlift(Player* player, Territory* start, Territory* target, int armies) {
    this->player=player;
    this->start=start;
    this->target=target;
    this->troops=armies;
    set_order_type("Airlift");
}
//COPY CONSTRUCTOR
Airlift::Airlift(const Airlift &other) : order(other) {
    this->player=other.getPlayer();
    this->start=other.getStart();
    this->target=other.getTarget();
    this->troops=other.getTroops();
    set_order_type("Airlift");
}
// = OPERATOR
Airlift &Airlift::operator=(const Airlift &o) {
    order::operator = (o);
    return *this;
}
//EXECUTE
void Airlift::execute() {
    if (validate()) {
        set_order_effect("Troops have moved.");
        cout << *get_order_effect() << endl;
    }
}
//VALIDATE
bool Airlift::validate() {
    if(start->getOwner() != player || start->getNumberOfArmies()<troops){
        return false;
    }else
        return true;
}
//GETTERS
Player *Airlift::getPlayer() const {
    return player;
}
Territory *Airlift::getStart() const {
    return start;
}
Territory *Airlift::getTarget() const {
    return target;
}
int Airlift::getTroops() const {
    return troops;
}
//SETTERS
void Airlift::setPlayer(Player *player) {
    Airlift::player = player;
}
void Airlift::setStart(Territory *start) {
    Airlift::start = start;
}
void Airlift::setTarget(Territory *target) {
    Airlift::target = target;
}
void Airlift::setTroops(int troops) {
    Airlift::troops = troops;
}
//DESTRUCTOR
Airlift::~Airlift() {
    player= nullptr;
    start= nullptr;
    target= nullptr;
}

#pragma endregion Airlift

#pragma region Negotiate
//NEGOTIATE
//DEFAULT CONSTRUCTOR
Negotiate::Negotiate() { set_order_type("Negotiate"); }
//CONSTRUCTOR
Negotiate::Negotiate(Player* player1,Player* player2) {
    this->player1=player1;
    this->player2=player2;
    set_order_type("Negotiate");
}
//COPY CONSTRUCTOR
Negotiate::Negotiate(const Negotiate &other) : order(other) {
    this->player1=other.getPlayer1();
    this->player2=other.getPlayer2();
    set_order_type("Negotiate");
}
// = OPERATOR
Negotiate &Negotiate::operator=(const Negotiate &o) {
    order::operator = (o);
    return *this;
}
//EXECUTE
void Negotiate::execute() {
    if (validate()) {
        set_order_effect("Attacks have been prevented until the end of turn.");
        cout << *get_order_effect() << endl;
    }
}
//VALIDATE
bool Negotiate::validate() {
    if(player1 == player2){
        return false;
    }
    return true;
}
//GETTERS
Player *Negotiate::getPlayer1() const {
    return player1;
}
Player *Negotiate::getPlayer2() const {
    return player2;
}
//SETTERS
void Negotiate::setPlayer1(Player *player1) {
    Negotiate::player1 = player1;
}
void Negotiate::setPlayer2(Player *player2) {
    Negotiate::player2 = player2;
}
//DESTRUCTOR
Negotiate::~Negotiate() {
    player1= nullptr;
    player2= nullptr;
}


#pragma endregion Negotiate

//ORDERS LIST IMPLEMENTATION
#pragma region OrderList
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
#pragma endregion OrderList



