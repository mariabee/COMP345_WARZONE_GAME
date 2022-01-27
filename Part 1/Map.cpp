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
Map::Map(int num_of_trs){
    this->num_of_trs = new int();
    *this->num_of_trs = num_of_trs;
    terr_nums = new list<int>[num_of_trs];
    territories = new Territory[num_of_trs];
    visited = new bool[num_of_trs];
}
Map::~Map(){
    delete num_of_trs;
    delete territories;
    delete terr_nums;
    delete visited;
    num_of_trs = nullptr;
    territories = nullptr;
    terr_nums = nullptr;
    visited = nullptr;
}

void Map::addBorder(int x, int y) {
    terr_nums[x-1].push_back(y);
}
void Map::cleanUpMap() {
    for (int i = 0; i < *num_of_trs; i++){
        terr_nums[i].sort();
    }
}
void Map::addTerritory(const Territory &t, const int ter_num, vector<int> const &bord_nums ) {
    //need to add code to check if territory already in position
    territories[ter_num - 1] = t;
    for (int i : bord_nums) {
        addBorder(ter_num, i);
    }
}
void Map::printMap() {
    for (int i = 0; i < *num_of_trs; i++) {
        cout << i+1 << " TERRITORY NAME TBA : ";
        for (int nbr:terr_nums[i]) {
            cout << nbr << " ";
        }
        cout << endl;
    }
}

void Map::traverse(int i) {
    visited[i] = true;
    for (int nbr:terr_nums[i]){
        if (!visited[nbr-1]){
            traverse(nbr-1);
        }
    }
}
bool Map::isConnected() {
    for (int i = 0; i < *num_of_trs; i++){
        visited[i] = false;
    }
    traverse(0);
    for (int i = 0; i < *num_of_trs; i++) {
        if (!visited[i]) {
            cout << "MAP IS NOT CONNECTED." << endl;
            return false;
        }
    }
    return true;
}



