#include "Map.h"

Map::Map(int num_of_trs){
    this->num_of_trs = new int();
    *this->num_of_trs = num_of_trs;
    terr_nums = new list<int>[num_of_trs];
    territories = new Territory[num_of_trs];
}
Map::~Map(){
    delete num_of_trs;
    delete territories;
    delete terr_nums;
    num_of_trs = NULL;
    territories = NULL;
    terr_nums = NULL;
}

void Map::addBorder(int x, int y) {
    terr_nums[x].push_back(y);
}
void Map::addTerritory(const Territory &t, int num) {
    territories[num] = t;
}
void Map::printMap() {
    for (int i = 0; i < *num_of_trs; i++) {
        cout << i << " TERRITORY NAME TBA : ";
        for (int nbr:terr_nums[i]) {
            cout << nbr << " ";
        }
        cout << endl;
    }
}

