#include "Map.h"
#include <vector>

Continent::Continent(const int ID, const string &name, int bonus, const string &color) {
    this->ID = ID;
    this->name = name;
    this->bonus = bonus;
    this->color = color;
    num_within = -1;
    subGraph = nullptr;
}

void Continent::addTerritories(const int IDs[], int num_of, Node *mapLinks[]) {
    this->num_within = num_of;
    subGraph = new Node*[num_within]();
    for (int i = 0; i < num_within; i++) {
        int ter = IDs[i];
        subGraph[i] = mapLinks[ter];
        mapLinks[ter]->value->setContinentId(ID);
    }
}
int Continent::getTerritoryID(int i) {
    return subGraph[i]->value->getId();
}
Territory Continent::getTerritory(int i) {
    return *subGraph[i]->value;
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

void Continent::setName(const string &_name) {
    this->name = _name;
}

int Continent::getBonus() const {
    return bonus;
}

void Continent::setBonus(int _bonus) {
    Continent::bonus = _bonus;
}

const string &Continent::getColor() const {
    return color;
}

void Continent::setColor(const string &_color) {
    Continent::color = _color;
}


Territory::Territory(int id, const string &name, int continentId) {
    this->ID=id;
    this->name=name;
    this->continent_ID=continentId;
    this->number_of_armies=0;
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



//Method to get a new node
void Map::AppendNode(int dest, Node* _head)
{
    Node  *newNode = new Node; //Create new Node
    Node *last = _head; //set last to head
    newNode->value = &territories[dest]; //Set its value to the address of the territory it represents
    newNode->next = nullptr;
    while (last->next != nullptr) {
        last = last->next; //Traverse the nodes
    }
    last->next = newNode; //put the new node after the last one

}
//MAP CONSTRUCTOR
//Takes an array of edges, an array of territories, number of territories, and number of edges.
Map::Map(Edge edges[], Territory territories[], int num_of_trs, int num_of_edges){
    head = new Node*[num_of_trs](); // An array of pointers to Nodes
    this->num_of_trs = num_of_trs;
    this->territories = territories;
    visited = new bool[num_of_trs];

    // initialize head pointer for all vertices, to corresponded with territory Id's.
    for (int i = 0; i < num_of_trs; i++) {
        head[i] = new Node;
        head[i]->value = &territories[i];
        head[i]->next = nullptr;
    }

    // add edges to the graph
    for (int i = 0; i < num_of_edges; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;
        // insert at the end
        AppendNode(dest, head[src]);


    }
}
Map::~Map(){
    for (int i = 0; i < num_of_trs; i++) {
        delete[] head[i];
    }
    delete[] head;
}
void Map::printNode(Node *ptr) {
    while (ptr != nullptr)
    {
        cout << ptr->value->getId() << " ";
        ptr = ptr->next;
    }
    cout << endl;
}
void Map::printMap() {
    for (int i = 0; i < num_of_trs; i++){
        printNode(head[i]); // print all vertices on a line
    }
}
int Map::countVisited(Node *ptr, int &count) {
    while (ptr != nullptr) {
        int i = ptr->value->getId();
        if (!visited[i]) {
            visited[i] = true;
            count++;
            countVisited(head[i], count);
        }
        ptr = ptr->next;
    }
    return count;
}
bool Map::isConnected(){
    int count = 0;
    int n = countVisited(head[0], count);
    if (n < num_of_trs) {
        return false;
    }
    return true;
}







