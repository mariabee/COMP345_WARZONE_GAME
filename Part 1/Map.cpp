#include "Map.h"
#include "../Part 2/Player.h"
#include <utility>
#include <iostream>
#include <sstream>
#include <fstream>

//TERRITORY IMPLEMENTATION

//CONSTRUCTORS
Territory::Territory() {
    name = new string("UNKNOWN");
    ID = -1;
    continent_ID = -1;
    number_of_armies = -1;
    edges = nullptr;
    edge_count = 0;
    player = nullptr;
    visited = false;
}
Territory::Territory(int id, string name, int continentId) {
    this->name = new string(move(name));
    this->ID=id;
    this->continent_ID=continentId;
    this->number_of_armies=0;
    edges = nullptr;
    edge_count = 0;
    player = nullptr;
    visited = false;
}
Territory::Territory(const Territory &t) {
    visited = t.visited;
    name = new string(*t.getName());
    player = t.getOwner();
    ID = t.getId();
    continent_ID = t.getContinentId();
    edge_count = t.getEdgeCount();
    number_of_armies = t.getNumberOfArmies();
    edges = new Territory*[edge_count]();
    for (int i = 0; i < edge_count; i++) {
        edges[i] = t.getEdges()[i];
    }
}
//COPY ASSIGNMENT
Territory &Territory::operator=(const Territory &t) {
    if (this == &t) {return *this; }
    delete[] edges;
    delete name;
    visited = t.visited;
    player = t.getOwner();
    edge_count = t.getEdgeCount();
    ID = t.getId();
    continent_ID = t.getContinentId();
    name = new string(*t.getName());
    edges = new Territory*[edge_count]();
    for (int i = 0; i < edge_count; i++) {
        edges[i] = t.getEdges()[i];
    }
    return *this;
}
//TERRITORY DESTRUCTOR
Territory::~Territory() {
    delete[] edges;
    delete name;
    name = nullptr;
    edges = nullptr;
    player = nullptr;
}
//OVERLOADED << OPERATOR
ostream &operator<<(ostream &os, const Territory &territory) {
    os << "ID: " << territory.getId() << "\tName: " << *territory.getName() << "\tContinent ID: " << territory.getContinentId();
    return os;
}
//METHOD TO ADD EDGES/BORDERS TO AN ARRAY OF TERRITORIES
void Territory::addEdges(vector<int> edge_nums, Territory *territories) {
    edge_count = edge_nums.size();
    int index;
    //reserve memory for array of Territory pointers
    this->edges = new Territory*[edge_count]();
    //For every edge
    for (int i = 0; i < edge_count; i++) {
        index = edge_nums[i] - 1;
        //Add the address of its equivalent territory to the array
        edges[i] = &territories[index];
    }
}

//ACCESSORS
int Territory::getId() const  { return ID; }
string *Territory::getName() const   { return name;}
int Territory::getContinentId() const{ return continent_ID; }
int Territory::getNumberOfArmies() const { return number_of_armies; }
int Territory::getEdgeCount() const {return edge_count; }
Territory **Territory::getEdges() const { return edges; }
Player *Territory::getOwner() const { return player; }
//MUTATORS
void Territory::setId(int id) { ID = id; }
void Territory::setName(string name_) {*this->name = move(name_);}
void Territory::setContinentId(int continentId) { this->continent_ID = continentId; }
void Territory::setNumberOfArmies(int numberOfArmies) { this->number_of_armies = numberOfArmies; }
void Territory::changeOwner(Player *player_) {this->player = player_;}
//CONTINENT IMPLEMENTATION

//CONSTRUCTORS
Continent::Continent() {
    name = new string("UNKNOWN");
    color = new string("UNKNOWN");
    ID = -1;
    bonus = -1;
    NUM_OF_TERS = -1;
    count = 0;
    subTerritories = nullptr;
}
Continent::Continent(const int ID, string _name, int bonus, string _color) {
    this->name = new string();
    this->color = new string();
    *this->name = move(_name);
    *this->color = move(_color);
    this->ID = ID;
    this->bonus = bonus;
    subTerritories = nullptr;
    count = 0;
    NUM_OF_TERS = -1;
}
Continent::Continent(const Continent &c) {
    name = new string(*c.getName());
    color = new string(*c.getColor());
    ID = c.getId();
    bonus = c.getBonus();
    count = c.count;
    NUM_OF_TERS = c.getNumOfTers();
    if (NUM_OF_TERS > 0) {
        subTerritories = new Territory *[NUM_OF_TERS]();
        for (int k = 0; k < NUM_OF_TERS; k++) {
            subTerritories[k] = c.getTerritories()[k];
        }
    }
}
//COPY ASSIGNMENT
Continent &Continent::operator=(const Continent &c) {
    if (this == &c)  return *this;
    delete[] subTerritories;
    delete name;
    delete color;
    name = new string(*c.getName());
    color = new string(*c.getColor());
    ID = c.getId();
    bonus = c.getBonus();
    NUM_OF_TERS = c.getNumOfTers();
    count = c.count;
    if (NUM_OF_TERS > 0) {
        subTerritories = new Territory *[NUM_OF_TERS]();
        for (int k = 0; k < NUM_OF_TERS; k++) {
            subTerritories[k] = c.getTerritories()[k];
        }
    }
    return *this;
}
//DESTRUCTOR
Continent::~Continent() {
    delete[] subTerritories;
    delete name;
    delete color;
    name = nullptr;
    color = nullptr;
    subTerritories = nullptr;

}
//OVERLOADED << OPERATOR
ostream &operator<<(ostream &os, const Continent &continent) {
    os << "ID: " << continent.ID << "\tName: " << *continent.getName() << "\tBonus: " << continent.bonus << "\tColor: "
       << *continent.getColor();
    return os;
}

//METHOD TO INITIALIZE SUBTERRITORY MAP
void Continent::createSubMap(int num_of_ters) {
    //Reserve memory for array of territory pointers
    subTerritories = new Territory*[num_of_ters]();
    NUM_OF_TERS = num_of_ters;
}
//METHOD TO ADD TERRITORIES TO SUBTERRITORY MAP
void Continent::addTerritory(Territory *territoryPtr) {
    if (subTerritories != nullptr) {
        subTerritories[count] = territoryPtr;
        count++;
    }
    else {
        cout << "PLEASE createSubMap() first." << endl;
    }
}

//ACCESSORS
string *Continent::getName() const { return name; }
string *Continent::getColor() const { return color; }
Territory** Continent::getTerritories()  const { return subTerritories; }
int Continent::getId() const { return ID; }
int Continent::getBonus() const { return bonus; }
int Continent::getNumOfTers() const {return NUM_OF_TERS;}

//MUTATORS
void Continent::setId(int id) { ID = id; }
void Continent::setName(string _name) { *name = move(_name);}
void Continent::setBonus(int _bonus) { this->bonus = _bonus; }
void Continent::setColor(string _color) {*color = move(_color);}

//MAP IMPLEMENTATION

//MAP CONSTRUCTORS
//Parameterized constructor : takes an array of Territory objects, Continent objects, and the size of each.
Map::Map(Territory territories[], int num_of_trs, Continent continents[], int num_of_cnts){
    this->NUM_OF_TRS = num_of_trs;
    this->NUM_OF_CNTS = num_of_cnts;
    this->territories = territories;
    this->continents = continents;
    visited = nullptr;
}
//Copy constructor
Map::Map(const Map &m) {
    NUM_OF_TRS = m.getNumOfTers();
    NUM_OF_CNTS = m.getNumOfCnts();
    visited = new bool[NUM_OF_TRS];
    territories = new Territory[NUM_OF_TRS]();
    continents = new Continent[NUM_OF_CNTS]();
    for (int i = 0; i < NUM_OF_TRS; i++) {
        territories[i] = *new Territory(m.getTerritories()[i]);
    }
    for (int i = 0; i < NUM_OF_CNTS; i++){
        continents[i] = *new Continent(m.getContinents()[i]);
    }
}
//Copy assignment
Map &Map::operator=(const Map &m) {
    if (this == &m) return *this;
    delete[] territories;
    NUM_OF_TRS = m.getNumOfTers();
    NUM_OF_CNTS = m.getNumOfCnts();
    territories = new Territory[NUM_OF_TRS]();
    for (int i = 0; i < NUM_OF_TRS; i++) {
        territories[i] = *new Territory(m.getTerritories()[i]);
    }
    for (int i = 0; i < NUM_OF_CNTS; i++){
        continents[i] = *new Continent(m.getContinents()[i]);
    }
    return *this;
}
//MAP DESTRUCTOR
Map::~Map(){
    delete[] territories;
    territories = nullptr;
    delete[] visited;
    visited = nullptr;
    delete[] continents;
    continents = nullptr;
}
//ACCESSORS
int Map::getNumOfTers() const {return NUM_OF_TRS;}
int Map::getNumOfCnts() const {return NUM_OF_CNTS;}
Territory *Map::getTerritories() const {return territories;}
Continent *Map::getContinents() const {return continents; }
//OVERLOADED << OPERATOR
ostream &operator<<(ostream &os, const Map &map) {
    for (int i = 0; i < map.NUM_OF_TRS; i++){
        os << map.territories[i].getId() << " ";
        int n = map.territories[i].getEdgeCount();
        for (int k = 0; k < n; k++) {
            os << map.territories[i].getEdges()[k]->getId() << " ";
        }
        os << endl;
    }
    return os;
}
//METHOD TO VISIT NODES AND COUNT HOW MANY VISITED
void Map::visitTerritories(Territory **e, int size, int &count) {
    //For every edge of a territory
    for (int i = 0; i < size; i++) {
        int index = e[i]->getId()-1;
        //if the edge is not visited...
        if (!territories[index].visited) {
            //visit it and add to count
            territories[index].visited = true;
            count++;
            //visit all of its edges
            visitTerritories(e[i]->getEdges(), e[i]->getEdgeCount(), count);
        }
    }
}
//METHOD TO VISIT ALL NODES WITHIN A CONTINENT
void Map::visitContinent(int id, Territory *t, int &count) {
        int n = t->getEdgeCount();
        //For every edge in a territory
        for (int i = 0; i < n; i++) {
            auto e = t->getEdges()[i];
            //If the edge is in the continent and not visited...
            if (e->getContinentId() == id && !e->visited) {
                //visit it and add one to count
                e->visited = true;
                count++;
                //visit all of its edges
                visitContinent(id, e, count);
            }
        }
}


//METHOD TO SEE IF MAP IS VALID
bool Map::validate() {
    //Set all territories to unvisited.
    for (int i = 0; i < NUM_OF_TRS; i++) {
        territories[i].visited = false;
    }
    int count = 0; //start count at 0.
    //Traverse all the territories, counting every territory that gets visited.
    visitTerritories(territories[0].getEdges(), territories[0].getEdgeCount(), count);
    //If not all territories get visited, map is not connected.
    if (count != NUM_OF_TRS) {
        cout << "Map is not connected." << endl;
        return false;
    }
    //Set all territories to unvisited,
    for (int i = 0; i < NUM_OF_TRS; i++) {
        territories[i].visited = false;
    }
    //For every continent...
    for (int i = 0; i < NUM_OF_CNTS; i++) {
        int n = continents[i].getNumOfTers();
        auto *c = &continents[i];
        count = 0;
        //If continent has more than one territory...
        if (n != 1) {
            //Traverse its territories, counting every one that gets visited
            visitContinent(c->getId(), c->getTerritories()[0], count);
            if (count != n) {
                cout << *c->getName() << " is not a connected subgraph." << endl;
                return false;
            }
        }
    }
    cout << "Map is valid. " << endl;
    return true;
}

//STATIC MAPLOADER METHOD
Map MapLoader::loadMap(const string &filename)  {
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
    delete str;
    str = nullptr;

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
    delete continentLine;
    continentLine = nullptr;

    int N = countries->size();
    // initialize Territory array
    auto *territories = new Territory[N];


    i = 0;
    int pastContinentId = 1; // keep track of previous continent ID
    int continentId; // keep track of current continent ID
    int c_count = 0; //keep a count of how many territories a continent has

    //For every line in countries
    for (auto &country: *countries) {
        stringstream ss(country);
        string word;
        //Go through each word and save the value to its corresponding territory
        while (ss >> word)
            if (counter == 0) {
                territories[i].setId(stoi(word)); //save the ID
                counter++;
            } else if (counter == 1) {
                territories[i].setName(word); //save the name
                counter++;
            } else if (counter == 2) {
                continentId = stoi(word);
                territories[i].setContinentId(continentId); //save the continent ID
                //if continent continentId has changed
                if (pastContinentId != continentId) {
                    //save the count of territories to the previous continent
                    continents[pastContinentId - 1].createSubMap(c_count);
                    //reset the count and pastContinentId
                    c_count = 0;
                    pastContinentId = continentId;
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
    //Add the last count of territories to the last continent
    continents[pastContinentId - 1].createSubMap(c_count);
    delete countries;
    countries = nullptr;

    //For every line in borders...
    for (auto &border: *borders) {
        istringstream ss(border);
        string word;
        vector<int> edges;
        int src;
        ss >> word;
        //set the first number as the source
        src = (stoi(word));
        //save all the other numbers in a vector of edges
        while (ss >> word) {
            edges.push_back(stoi(word));
        }
        //Add the edges to the territory whose id matches the src
        territories[src-1].addEdges(edges, territories);
        //reset the vector
        edges.clear();
    }
    delete borders;
    borders = nullptr;

    //For every territory...
    for (i = 0; i < N; i++) {
        //Get the territory's continent ID
        int k = territories[i].getContinentId();
        //Add a reference to the territory to its continent
        continents[k - 1].addTerritory(&territories[i]);
    }
    return {territories, N, continents, C};
}











