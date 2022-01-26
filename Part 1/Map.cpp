#include "Map.h"
#include <vector>
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

