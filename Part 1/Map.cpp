#include "Map.h"
#include <vector>

Continent::Continent(const int ID, const string &name, int bonus, const string &color) {
    this->ID = ID;
    this->name = name;
    this->bonus = bonus;
    this->color = color;
}

ostream &operator<<(ostream &os, const Continent &continent) {
    os << "ID: " << continent.ID << "\tName: " << continent.name << "\tBonus: " << continent.bonus << "\tColor: "
       << continent.color;
    return os;
}

int Continent::getId() const {
    return ID;
}

void Continent::setId(int id) {
    ID = id;
}

const string &Continent::getName() const {
    return name;
}

void Continent::setName(const string &name) {
    Continent::name = name;
}

int Continent::getBonus() const {
    return bonus;
}

void Continent::setBonus(int bonus) {
    Continent::bonus = bonus;
}

const string &Continent::getColor() const {
    return color;
}

void Continent::setColor(const string &color) {
    Continent::color = color;
}


Territory::Territory(int id, const string &name, int continentId) {
    this->ID=id;
    this->name=name;
    this->continent_ID=continentId;
    this->number_of_armies=0;
    this->continent= nullptr;
}

ostream &operator<<(ostream &os, const Territory &territory) {
    os << "ID: " << territory.ID << "\tName: " << territory.name << "\tContinent ID: " << territory.continent_ID;
    return os;
}

int Territory::getId() const {
    return ID;
}

void Territory::setId(int id) {
    ID = id;
}

const string &Territory::getName() const {
    return name;
}

void Territory::setName(const string &name) {
    Territory::name = name;
}

int Territory::getContinentId() const {
    return continent_ID;
}

void Territory::setContinentId(int continentId) {
    continent_ID = continentId;
}

int Territory::getNumberOfArmies() const {
    return number_of_armies;
}

void Territory::setNumberOfArmies(int numberOfArmies) {
    number_of_armies = numberOfArmies;
}


void Territory::setContinent(Continent *continent) {
    Territory::continent = continent;
}

//Method to get a new node
Node* Map::getNewNode(int dest, Node* head)
{
    //Create new Node
    Node  *newNode = new Node;
    newNode->value = &territories[dest]; //Set its value to the address of the territory it represents
    newNode->next = head; //Set its next node value to the head
    if (head != nullptr) {
        head->previous = newNode;
    }
    return newNode;
}
//MAP CONSTRUCTOR
//Takes an array of edges, an array of territories, number of territories, and number of edges.
Map::Map(Edge edges[], Territory territories[], int num_of_trs, int num_of_edges){
    head = new Node*[num_of_trs](); // An array of pointers to Nodes
    this->num_of_trs = num_of_trs;
    this->territories = territories;

    // initialize head pointer for all vertices, to corresponded with territory Id's.
    for (int i = 0; i < num_of_trs; i++) {
        head[i] = getNewNode(i, nullptr);
    }

    // add edges to the graph
    for (int i = 0; i < num_of_edges; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;

        // insert at the end
        Node *newNode = getNewNode(dest, head[src]);

        // point head pointer to the new node
        head[src] = newNode;
    }
}
Map::~Map(){
    for (int i = 0; i < num_of_trs; i++) {
        delete[] head[i];
    }
    delete[] head;
}
void Map::printNode(Node *ptr) {
    while (ptr->next != nullptr)
    {
        ptr = ptr->next;
    }
    while (ptr != nullptr) {
        cout << ptr->value->getId() << " ";
        ptr = ptr->previous;
    }
    cout << endl;
}
void Map::printMap() {
    for (int i = 0; i < num_of_trs; i++){
        printNode(head[i]); // print all vertices on a line
    }
}







