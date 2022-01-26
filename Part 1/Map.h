#pragma once
#include <list>
#include <iostream>

using namespace std;
class Territory {
    int number;
    string name;
public:
    Territory() {

    }
};
class Map {
    int *num_of_trs;
    list<int> *terr_nums;
    Territory *territories;
public :
    explicit Map(int num_of_trs);
    ~Map();
    void addBorder(int x, int y);
    void addTerritory(const Territory &t, int num);
    void printMap();
};
class continent {

};