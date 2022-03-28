#include "Orders.h"
#include<cstdlib>
#include "../Part 2/Player.h"
#include <bits/stdc++.h>

// BASE CLASS IMPLEMENTATION
#pragma region Order
//DEFAULT CONSTRUCTOR
order::order()
{
    order_effect_ = new string();
    order_type_ = new string();
    player = nullptr;
}
//COPY CONSTRUCTOR
order::order(const order& other)
{
    order_type_ = new string(*other.get_order_type());
    order_effect_ = new string(*other.get_order_effect());
    player = other.get_player();
}

// = OPERATOR
order &order::operator=(const order &o) {
    if (this == &o) return *this;
    delete order_effect_;
    delete order_type_;
    order_effect_ = new string(*o.get_order_effect());
    order_type_ = new string(*o.get_order_type());
    return *this;
}
//DESTRUCTOR
order::~order()
{
    delete order_effect_;
    delete order_type_;
    order_effect_ = nullptr;
    order_type_ = nullptr;
    player = nullptr;
}

//ACCESSOR IMPLEMENTATION
string *order::get_order_type() const { return order_type_;}
string *order::get_order_effect() const {return order_effect_;}
Player *order::get_player() const {return player; }
//MUTATOR IMPLEMENTATION
void order::set_order_type(string order) { *order_type_ = move(order); }
void order::set_order_effect(string effect) { *order_effect_ = move(effect); }
void order::set_player(Player *player_) { this->player = player_; }
//STREAM INSERTION OPERATOR IMPLEMENTATION
ostream& operator << (ostream& stream, const order& order_obj) {
    stream << *order_obj.get_order_type() << " has been ordered ";
    if (order_obj.get_player()) {
        stream << "by " << *order_obj.get_player() << ".";
    }
    else {
        stream << "by unknown player.";
    }
    cout << endl;
    if (!order_obj.get_order_effect()->empty()) {
        stream << *order_obj.get_order_effect() << endl;
    }
    return stream;
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
    territory = nullptr;
    numberOfArmies = 0;
    set_order_type("Deploy");
}
//CONSTRUCTOR
Deploy::Deploy(Player *p, Territory *t, int nbr) {
    this->territory=t;
    this->numberOfArmies=nbr;
    set_order_type("Deploy");
    set_player(p);
}
//COPY CONSTRUCTOR
Deploy::Deploy(const Deploy &other) : order(other) {
    this->numberOfArmies = other.getNumberOfArmies();
    this->territory = other.getTerritory();
}
// = OPERATOR
Deploy &Deploy::operator=(const Deploy &o)  {
    if (this == &o) return *this;
    order::operator = (o);
    this->numberOfArmies = o.getNumberOfArmies();
    this->territory = o.getTerritory();
    return *this;
}
//EXECUTE
void Deploy::execute() {
    if (validate()) {
        int n = territory->getNumberOfArmies() + numberOfArmies;
        territory->setNumberOfArmies(n);
        get_player()->setArmies(get_player()->getArmies()-numberOfArmies);
        cout<<*territory->getName()<<" now has "<< n <<" armies.\n";
        set_order_effect("Armies have been deployed.");
    }
}
//VALIDATE
bool Deploy::validate() {
    if (!territory) {
        set_order_effect("Order was missing information and will not be executed.");
    }
    if(territory->getOwner() != get_player()){
        set_order_effect("Order was not valid and will not be executed.");
        return false;
    }
    if (numberOfArmies > get_player()->getArmies()){
        set_order_effect("Player does not have enough armies.");
        return false;
    }else
        return true;
}
//GETTERS
Territory *Deploy::getTerritory() const {
    return territory;
}
int Deploy::getNumberOfArmies() const {
    return numberOfArmies;
}
//SETTERS
void Deploy::setTerritory(Territory *territory) {
    Deploy::territory = territory;
}
void Deploy::setNumberOfArmies(int numberOfArmies) {
    Deploy::numberOfArmies = numberOfArmies;
}
//DESTRUCTOR
Deploy::~Deploy() {
    territory= nullptr;
}

#pragma endregion Deploy

#pragma region Advance
//ADVANCE
//DEFAULT CONSTRUCTOR
Advance::Advance() {
    start = nullptr;
    target = nullptr;
    armies = 0;
    deck = nullptr;
    set_order_type("Advance");
}
//CONSTRUCTOR
Advance::Advance(Player* player,Territory* start, Territory* target, int armies,Deck *deck) {
    this->start=start;
    this->target=target;
    this->armies=armies;
    set_player(player);
    this->deck=deck;
    set_order_type("Advance");
}
//COPY CONSTRUCTOR
Advance::Advance(const Advance &other) : order(other) {
    this->start = other.getStart();
    this->target = other.getTarget();
    this->armies = other.getArmies();
    this->deck = other.deck;
}
// = OPERATOR
Advance&Advance::operator=(const Advance &other)  {
    if (this == &other) return *this;
    order::operator = (other);
    this->start = other.getStart();
    this->target = other.getTarget();
    this->armies = other.getArmies();
    this->deck = other.deck;
    return *this;
}
//EXECUTE
void Advance::execute() {
    if (validate()) {
        if(start->getOwner() == target->getOwner()){
            target->setNumberOfArmies(target->getNumberOfArmies()+armies);
            start->setNumberOfArmies(start->getNumberOfArmies()-armies);
            cout << *get_player() << " has moved " << armies << " troops from " << *start->getName() << " to " << *target->getName() << endl;
            set_order_effect("Player has moved troops");
        }else{
            cout << "An attack has been initiated." << endl;
            float random;
            srand(time(NULL));
            while(target->getNumberOfArmies() != 0 && start->getNumberOfArmies() != 0){
                random=((float)rand() / (float)RAND_MAX );
                if(random>0.4){
                    target->setNumberOfArmies(target->getNumberOfArmies()-1);
                }
                if(random>0.3){
                    start->setNumberOfArmies(start->getNumberOfArmies()-1);
                }
            }
            if(target->getNumberOfArmies()==0){
                get_player()->addTerritory(target);
                cout << *target->getName() << " has been conquered " << " by " << *get_player();
                set_order_effect("New territory has been conquered.");
                if(!get_player()->isCardWon()){
                    get_player()->getHand()->drawFromDeck(deck);
                    get_player()->setCardWon(true);
                }
            }
            else{
                cout << *get_player() << " has lost the battle for " << *target->getName() << "." << endl;
                set_order_effect("Battle lost.");
            }
        }
    }
}
//VALIDATE
bool Advance::validate() {
    if (armies <= 0) {
        return false;
    }
    if (!start || !target) {
        set_order_effect("Order was missing information and will not be executed.");
        return false;
    }
    if (get_player()->getCannotAttack()->size() > 0) {
        cout << *target << endl;
        Player *owner = target->getOwner();
        for (int i = 0; i < get_player()->getCannotAttack()->size(); i++) {
            if (owner && owner == (get_player()->getCannotAttack()->at(i))) {
                set_order_effect("A NEGOTIATION IS IN ORDER. THE ORDER WILL NOT BE EXECUTED");
                return false;
            }
        }
    }
    if(!start->getOwner() || start->getOwner() != get_player() || !isBeside(start,target) || start->getNumberOfArmies() < armies){
        set_order_effect("Order was not valid and will not be executed.");
        return false;
    } else
        return true;
}
//SETTERS
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
    start= nullptr;
    target= nullptr;
    deck= nullptr;
}
#pragma endregion Advance

#pragma region Bomb
//BOMB
//DEFAULT CONSTRUCTOR
Bomb::Bomb() {
    start = nullptr;
    target = nullptr;
    set_order_type("Bomb"); }
//CONSTRUCTOR
Bomb::Bomb(Player* player, Territory* start, Territory* target) {
    this->start=start;
    this->target=target;
    set_order_type("Bomb");
    set_player(player);
}
//COPY CONSTRUCTOR
Bomb::Bomb(const Bomb &other) : order(other){
    this->start=other.getStart();
    this->target=other.getTarget();
}
// = OPERATOR
Bomb&Bomb::operator=(const Bomb &o) {
    if (this == &o) return *this;
    order::operator = (o);
    this->start=o.getStart();
    this->target=o.getTarget();
    return *this;
}
void Bomb::execute() {
    if (validate()) {
        target->setNumberOfArmies((target->getNumberOfArmies())/2);
        set_order_effect("Territory has been bombed.");
    }
    cout << *get_order_effect() << endl;
}
bool Bomb::validate() {
    if (start == nullptr || target == nullptr) {
        set_order_effect("Order was missing information and will not be executed.");
        return false;
    }
    if (get_player()->getCannotAttack()->size() > 0) {
        for (int i = 0; i < get_player()->getCannotAttack()->size(); i++) {
            if (target->getOwner() == (get_player()->getCannotAttack()->at(i))) {
                set_order_effect("A NEGOTIATION IS IN ORDER. THE ORDER WILL NOT BE EXECUTED");
                return false;
            }
        }
    }
    if(start->getOwner() != get_player() || target->getOwner() == get_player() || !isBeside(start,target)){
        set_order_effect("Order was not valid and will not be executed.");
        return false;
    }else
        return true;
    //Returns true if player owns the territory, territory is beside target, and the target is not owned by player.
}
//GETTERS
Territory *Bomb::getStart() const {
    return start;
}
Territory *Bomb::getTarget() const {
    return target;
}
//SETTERS
void Bomb::setStart(Territory *start) {
    Bomb::start = start;
}
void Bomb::setTarget(Territory* target){
    Bomb::target = target;
}
//DESTRUCTOR
Bomb::~Bomb(){
    start= nullptr;
    target= nullptr;
}
#pragma endregion Bomb

#pragma region Blockade
//BLOCKADE
//BLOCKADE
//DEFAULT CONSTRUCTOR
Blockade::Blockade() {
    territory = nullptr;
    set_order_type("Blockade"); }
//CONSTRUCTOR
Blockade::Blockade(Player* player, Territory* territory, Player* neutral) {
    this->territory=territory;
    set_order_type("Blockade");
    set_player(player);
    this->neutral = neutral;
}
//COPY CONSTRUCTOR
Blockade::Blockade(const Blockade &other) : order(other) {
    this->territory=other.getTerritory();
}
// = OPERATOR
Blockade &Blockade::operator=(const Blockade &o) {
    if (this == &o) return *this;
    order::operator = (o);
    this->territory=o.getTerritory();
    this->neutral=o.getNeutral();
    return *this;
}
//EXECUTE
void Blockade::execute() {
    if (validate()) {
        territory->setNumberOfArmies(territory->getNumberOfArmies()*2);
        Player *owner = territory->getOwner();
        if (owner) {
            territory->getOwner()->removeTerritory(territory);
        }
        set_order_effect("Troops have DOUBLED. The territory is now NEUTRAL. ");
    }
    cout << *get_order_effect() << endl;
}
//VALIDATE
bool Blockade::validate() {
    if (!territory) {
        set_order_effect("Order was missing information and will not be executed.");
        return false;
    }
    if(territory->getOwner() != get_player()){
        set_order_effect("Order was not valid and will not be executed.");
        return false;
    }else
        return true;
    //Returns true if player owns the territory
}
//GETTERS

Territory *Blockade::getTerritory() const {
    return territory;
}
//SETTERS

void Blockade::setTerritory(Territory *territory) {
    Blockade::territory = territory;
}
//DESTRUCTOR
Blockade::~Blockade() {
    territory = nullptr;
}

Player *Blockade::getNeutral() const {
    return neutral;
}

void Blockade::setNeutral(Player *neutral) {
    Blockade::neutral = neutral;
}

#pragma endregion Blockade

#pragma region Airlift
//AIRLIFT
//DEFAULT CONSTRUCTOR
Airlift::Airlift() {
    this->start= nullptr;
    this->target= nullptr;
    this->troops= 0;
    set_order_type("Airlift"); }
//CONSTRUCTOR
Airlift::Airlift(Player* player, Territory* start, Territory* target, int armies) {
    this->start=start;
    this->target=target;
    this->troops=armies;
    set_order_type("Airlift");
    set_player(player);
}
//COPY CONSTRUCTOR
Airlift::Airlift(const Airlift &other) : order(other) {
    this->start=other.getStart();
    this->target=other.getTarget();
    this->troops=other.getTroops();
}
// = OPERATOR
Airlift &Airlift::operator=(const Airlift &other) {
    if (this == &other) return *this;
    order::operator = (other);
    this->start=other.getStart();
    this->target=other.getTarget();
    this->troops=other.getTroops();
    return *this;
}
//EXECUTE
void Airlift::execute() {
    if (validate()) {
        target->setNumberOfArmies(target->getNumberOfArmies()+troops);
        start->setNumberOfArmies(start->getNumberOfArmies()-troops);
        set_order_effect("Troops have moved.");
    }
    cout << *get_order_effect() << endl;
}
//VALIDATE
bool Airlift::validate() {
    if (!start) {
        set_order_effect("Order was missing information and will not be executed.");
        return false;
    }
    if(start->getOwner() != get_player() || target->getOwner() != get_player() || start->getNumberOfArmies() < troops){
        set_order_effect("Order was not valid and will not be executed.");
        return false;
    }else
        return true;
    //Returns true if player owns start territory and has enough armies on the territory to move.
}
//GETTERS
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
    start= nullptr;
    target= nullptr;
}

#pragma endregion Airlift

#pragma region Negotiate
//NEGOTIATE
//DEFAULT CONSTRUCTOR
Negotiate::Negotiate() {
    player2 = nullptr;
    set_order_type("Negotiate"); }
//CONSTRUCTOR
Negotiate::Negotiate(Player* player1,Player* player2) {
    this->player2=player2;
    set_order_type("Negotiate");
    set_player(player1);
}
//COPY CONSTRUCTOR
Negotiate::Negotiate(const Negotiate &other) : order(other) {
    this->player2=other.getPlayer2();
}
// = OPERATOR
Negotiate &Negotiate::operator=(const Negotiate &o) {
    if (this == &o) return *this;
    order::operator = (o);
    this->player2=o.getPlayer2();
    return *this;
}
//EXECUTE
void Negotiate::execute() {
    if (validate()) {
        get_player()->getCannotAttack()->push_back(player2);
        player2->getCannotAttack()->push_back(get_player());
        set_order_effect("Attacks have been prevented until the end of turn.");
    }
    cout << *get_order_effect() << endl;
}
//VALIDATE
bool Negotiate::validate() {

    if (!player2 || !get_player()) {
        set_order_effect("Order was missing information and will not be executed.");
        return false;
    }
    if(get_player() == player2){
        set_order_effect("Order was not valid and will not be executed.");
        return false;
    }
    return true;
    //Returns true if players are different
}
//GETTERS
Player *Negotiate::getPlayer2() const {
    return player2;
}
//SETTERS
void Negotiate::setPlayer2(Player *player2) {
    Negotiate::player2 = player2;
}
//DESTRUCTOR
Negotiate::~Negotiate() {
    player2= nullptr;
}


#pragma endregion Negotiate

//ORDERS LIST IMPLEMENTATION
#pragma region OrderList
void OrdersList::add(order* o) {
    list->push_back(o);
}
bool OrdersList::move(order* o, int position) {
    if (position >= list->size() || position < 0) {
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
    else {
        cout << *o->get_order_type() << " was not found. " << endl;
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
order * OrdersList::popTop() {
    order *o = list->back();
    list->pop_back();
    return o;
}
OrdersList::OrdersList(){
    list = new vector<order *>();
    ptr = new vector<order *>::iterator();
}
OrdersList::OrdersList(const OrdersList &other) {
    list = new vector<order *>();
    ptr = new vector<order *>::iterator();
    for (order *o : *other.getList()) {
        add(o);
    }
}
OrdersList &OrdersList:: operator=(const OrdersList& o) {
    if (this == &o) return *this;
    for (order *o : *list) {
        delete o;
    }
    list->clear();
    for (order *o : *o.getList()) {
        add(o);
    }
    return *this;
}

OrdersList::~OrdersList() {
    //Deleting OrdersList also currently deletes the orders it references.
    for (order *o : *list) {
        delete o;
    }
    list->clear();
    delete list;
    delete ptr;
    list = nullptr;
    ptr = nullptr;
}
vector<order *> *OrdersList::getList() const { return list; }

ostream &operator<<(ostream &out, const OrdersList &orderlist) {
    for (order *o : *orderlist.list) {
        out << *o;
    }
    return out;
}

#pragma endregion OrderList


