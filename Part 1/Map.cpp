#include "Map.h"
#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

//TERRITORY IMPLEMENTATION

Territory::Territory(int id, string name, int continentId) {
    this->name = new string();
    *this->name= move(name);
    this->ID=id;
    this->continent_ID=continentId;
    this->number_of_armies=0;
    edges = nullptr;
    edge_count = 0;
}
Territory::Territory() {
    name = new string();
    *name = "UNKNOWN";
    ID = -1;
    continent_ID = -1;
    number_of_armies = -1;
    edges = nullptr;
    edge_count = 0;
}

void Territory::addEdges(vector<int> edge_nums, Territory *territories) {
    edge_count = edge_nums.size();
    int index;
    this->edges = new Territory[edge_count]();
    for (int i = 0; i < edge_count; i++) {
        index = edge_nums[i] - 1;
        edges[i] = territories[index];
    }
}
Territory *Territory::getEdges(){ return edges; }

ostream &operator<<(ostream &os, const Territory &territory) {
    os << "ID: " << territory.ID << "\tName: " << territory.getName() << "\tContinent ID: " << territory.continent_ID;
    return os;
}

//ACCESSORS
int Territory::getId() const  { return ID; }
string Territory::getName() const   { return *name;}
int Territory::getContinentId() const{ return continent_ID; }
int Territory::getNumberOfArmies() const { return number_of_armies; }
int Territory::getEdgeCount() const {return edge_count; }
//MUTATORS
void Territory::setId(int id) { ID = id; }
void Territory::setName(string name_) {*this->name = move(name_);}
void Territory::setContinentId(int continentId) { this->continent_ID = continentId; }
void Territory::setNumberOfArmies(int numberOfArmies) { this->number_of_armies = numberOfArmies; }
//TERRITORY DESTRUCTOR
Territory::~Territory() {
    /*
    delete name;
    name = nullptr;*/

}
//MAP IMPLEMENTATION

//MAP CONSTRUCTOR
//Aan array of territories, number of territories
Map::Map(Territory territories[], int num_of_trs){
    this->NUM_OF_TRS = num_of_trs;
    this->territories = territories;
    visited = new bool[NUM_OF_TRS];
}
//MAP DESTRUCTOR
Map::~Map(){
    delete[] territories;
    territories = nullptr;
    delete[] visited;
    visited = nullptr;
}
//PRINT METHOD
void Map::printEdges(Territory *ptr, int n) {
    for (int i = 0; i < n; i++) {
        cout << ptr[i].getId() << " ";
    }
    cout << endl;
}
//PRINT MAP METHOD
void Map::printMap() const {
    for (int i = 0; i < NUM_OF_TRS; i++){
        cout << territories[i].getId() << " ";
        printEdges(territories[i].getEdges(), territories[i].getEdgeCount()); // print all edges
    }
}
//METHOD TO VISIT NODES AND COUNT HOW MANY VISITED
void Map::countVisited(Territory *e, int &count, int size) {

    for (int i = 0; i < size; i++) {
        int index = e[i].getId()-1;
        if (!visited[index]) {
            visited[index] = true;
            count++;
            countVisited(territories[index].getEdges(), count, territories[index].getEdgeCount());
        }
    }

}
//METHOD TO SEE IF MAP IS CONNECTED
bool Map::isConnected(){
    int count = 0;
    for (int i = 1; i < NUM_OF_TRS; i++){
        visited[i] = false;
    }
    countVisited(territories[0].getEdges(), count, territories[0].getEdgeCount());
    if (count < NUM_OF_TRS) {
        return false;
    }
    return true;
}
/*
Territory::Territory(int id, string name, int continentId) {
    this->name = new string();
    *this->name= name;
    this->ID=id;
    this->continent_ID=continentId;
    this->number_of_armies=0;
}
Territory::Territory() {
    name = new string();
    *name = "UNKNOWN";
    ID = -1;
    continent_ID = -1;
    number_of_armies = -1;
}

ostream &operator<<(ostream &os, const Territory &territory) {
    os << "ID: " << territory.ID << "\tName: " << territory.name << "\tContinent ID: " << territory.continent_ID;
    return os;
}
//ACCESSORS
int Territory::getId() const  { return ID; }
string Territory::getName() const   { return *name;}
int Territory::getContinentId() const{ return continent_ID; }
int Territory::getNumberOfArmies() const { return number_of_armies; }
//MUTATORS
void Territory::setId(int id) { ID = id; }
void Territory::setName(string name_) {*this->name = name_;}
void Territory::setContinentId(int continentId) { this->continent_ID = continentId; }
void Territory::setNumberOfArmies(int numberOfArmies) { this->number_of_armies = numberOfArmies; }

//MAP IMPLEMENTATION

//Method to get a new node
void Map::AppendNode(int dest, Node* _head)
{
    Node  *newNode = new Node; //Create new Node
    Node *last = _head; //set last to head
    newNode->value = &territories[dest-1]; //Set its value to the address of the territory it represents
    newNode->next = nullptr;
    while (last->next != nullptr) {
        last = last->next; //Traverse the nodes
    }
    last->next = newNode; //put the new node after the last one

}
//MAP CONSTRUCTOR
//Takes a vector of edges, an array of territories, number of territories, and number of edges.
Map::Map(const vector<Edge> &edges, Territory territories[], int num_of_trs){
    head = new Node*[num_of_trs](); // An array of pointers to Nodes
    this->NUM_OF_TRS = num_of_trs;
    this->territories = territories;
    visited = new bool[NUM_OF_TRS];
    // initialize head pointer for all vertices, to corresponded with territory.
    for (int i = 0; i < NUM_OF_TRS; i++) {
        head[i] = new Node;
        head[i]->value = &territories[i];
        head[i]->next = nullptr;
    }
    // add edges to the graph
    for (Edge edge : edges) {
        int src = edge.src;
        int dest = edge.dest;
        // insert at the end
        AppendNode(dest, head[src-1]);
    }
}
//MAP DESTRUCTOR
Map::~Map(){
    for (int i = 0; i < NUM_OF_TRS; i++) {
        delete[] head[i];
    }
    delete[] head;
}
//PRINT NODE METHOD
void Map::printNode(Node *ptr) {
    while (ptr != nullptr)
    {
        cout << ptr->value->getId() << " ";
        ptr = ptr->next;
    }
    cout << endl;
}
//PRINT MAP METHOD
void Map::printMap() const {
    for (int i = 0; i < NUM_OF_TRS; i++){
        printNode(head[i]); // print all vertices on a line
    }
}
//METHOD TO VISIT NODES AND COUNT HOW MANY VISITED
int Map::countVisited(Node *ptr, int &count) {
    while (ptr != nullptr) {
        int index = ptr->value->getId()-1;
        if (!visited[index]) {
            visited[index] = true;
            count++;
            countVisited(head[index], count);
        }
        ptr = ptr->next;
    }
    return count;
}
//METHOD TO SEE IF MAP IS CONNECTED
bool Map::isConnected(){
    int count = 0;
    for (int i = 0; i < NUM_OF_TRS; i++){
        visited[i] = false;
    }
    countVisited(head[0], count);
    if (count < NUM_OF_TRS) {
        return false;
    }
    return true;
}*/
//CONTINENT IMPLEMENTATION

Continent::Continent() {
    name = new string();
    color = new string();
    *name = "UNKNOWN";
    *color = "UNKNOWN";
    ID = -1;
    bonus = -1;
    i = 0;
    subTerritories = nullptr;
    NUM_OF_TERS = -1;
}

Continent::Continent(const int ID, string _name, int bonus, string _color) {
    this->name = new string();
    this->color = new string();
    *this->name = move(_name);
    *this->color = move(_color);
    this->ID = ID;
    this->bonus = bonus;
    subTerritories = nullptr;
    i = 0;
    NUM_OF_TERS = -1;
}
void Continent::createSubMap(int num_of_ters) {
    subTerritories = new Territory*[num_of_ters]();
    NUM_OF_TERS = num_of_ters;
}
void Continent::addTerritory(Territory &mapLink) {
    subTerritories[i] = &mapLink;
    i++;
}

ostream &operator<<(ostream &os, const Continent &continent) {
    os << "ID: " << continent.ID << "\tName: " << continent.getName() << "\tBonus: " << continent.bonus << "\tColor: "
       << continent.getColor();
    return os;
}

//MUTATORS
void Continent::setId(int id) { ID = id; }
void Continent::setName(string _name) { *name = move(_name);}
void Continent::setBonus(int _bonus) { this->bonus = _bonus; }
void Continent::setColor(string _color) {*color = move(_color);}
//ACCESSORS
string Continent::getName() const { return *name; }
int Continent::getId() const { return ID; }
int Continent::getBonus() const { return bonus; }
string Continent::getColor() const { return *color; }
Territory* Continent::getTerritories()  const { return *subTerritories; }
int Continent::getNumOfTers() const {return NUM_OF_TERS;}
int* Continent::getTerritoryIDs() {
    int* ids = new int[i]();
    for (int k = 0; k < i; k++) {
        ids[k] = subTerritories[k]->getId();
    }
    return ids;
}

Continent::~Continent() {
    delete[] subTerritories;
    delete name;
    delete color;
}

MapLoader::MapLoader(const string& filename) {
    string *str;
    int counter{0};
    vector<string> *continentLine,*countries,*borders;

    str = new string{};
    continentLine = new vector<string>{};
    countries = new vector<string>{};
    borders = new vector<string>{};

    //Read from file
    ifstream input(filename);
    //If file is not found
    if (!input) {
        cerr << "Error! Cannot find the file you're looking for!" << endl;
        exit(0);
    }
    while (getline(input, *str)) {
//        Read the continent part
        if (*str == "[continents]") {
            while (getline(input, *str) && !str->empty()) {
                continentLine->push_back(*str);
            }
        }

//        Read the country part
        if (*str == "[countries]") {
            while (getline(input, *str) && !str->empty()) {
                countries->push_back(*str);
            }
        }

//        Read the border part
        if (*str == "[borders]") {
            while (getline(input, *str) && !str->empty()) {
                borders->push_back(*str);
            }
        }
    }
    input.close();

//    Check for invalid file
    if (continentLine->empty() || borders->empty() || countries->empty()) {
        cerr << "Invalid map file" << endl;
        exit(0);
    }
    int C = continentLine->size();
    auto *continents = new Continent[C];
    int i = 0;
//    Split the string and store the components into the continents array
    for (auto &continent: *continentLine) {
        istringstream ss(continent);
        string word;
        while (ss >> word) {
            if (counter == 0) {
                continents[i].setId(i + 1);
                continents[i].setName(word);
                counter++;
            } else if (counter == 1) {
                continents[i].setBonus(stoi(word));
                counter++;
            } else if (counter == 2) {
                continents[i].setColor(word);
                counter = 0;
            }
        }
        i++;
    }


    int N = countries->size();
    auto *territories = new Territory[N];

    // Split the string and store the components into territories array
    i = 0;
    //keep track of the continent id that each territory has
    int past_ID = 1;
    int id;
    //keep a count of how many territories have the same continent id
    int c_count = 0;
    for (auto &country: *countries) {
        stringstream ss(country);
        string word;
        while (ss >> word)
            if (counter == 0) {
                territories[i].setId(stoi(word));
                counter++;
            } else if (counter == 1) {
                territories[i].setName(word);
                counter++;
            } else if (counter == 2) {
                id = stoi(word);
                territories[i].setContinentId(id);
                //if continent id has changed
                if (past_ID != id) {
                    //save the count of territories to the old continent
                    continents[past_ID - 1].createSubMap(c_count);
                    //reset the count and past-id
                    c_count = 0;
                    past_ID = id;
                }
                c_count++;
                counter++;
            } else if (counter == 3) { // Don't need this component
                counter++;
                continue;
            } else if (counter == 4) { // Don't need this component
                counter = 0;
                continue;
            }
        i++;
    }
    //Add the last count of territories
    continents[past_ID - 1].createSubMap(c_count);

    //Split the string and store the border numbers in a vector
    for (auto &border: *borders) {
        istringstream ss(border);
        string word;
        vector<int> edges;
        int src;
        ss >> word;
        src = (stoi(word));
        while (ss >> word) {
            edges.push_back(stoi(word));
        }
        //Add the edges to the current territory object
        territories[src-1].addEdges(edges, territories);
        //reset the vector
        edges.clear();
    }

    //Create the map
    map = new Map(territories, N);

    if (!map->isConnected()) {
        cout << "MAP IS NOT CONNECTED" << endl;
    } else {
        cout << "MAP IS CONNECTED" << endl;
    }

    for (i = 0; i < N; i++) {
        int k = map->territories[i].getContinentId();
        continents[k - 1].addTerritory(map->territories[i]);
    }
    int n = continents[0].getNumOfTers();
    int *terIds;
    terIds = continents[0].getTerritoryIDs();
    for (i = 0; i < n; i++) {
        cout << terIds[i] << " ";
    }
    cout << endl;
}

Map MapLoader::getMap() const {
    return *map;
}







