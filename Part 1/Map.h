#pragma once
#include <list>
#include <iostream>
#include <vector>

using namespace std;
class Territory {
    int number;
    string *name;
public:
    Territory(){}
    Territory(string name) {
        this->name = &name;
    }
};
class Map {
    int *num_of_trs;
    list<int> *terr_nums;
    Territory *territories;
    bool *visited;
    void addBorder(int x, int y);
    void traverse(int i);
public :
    explicit Map(int num_of_trs);
    ~Map();
    void cleanUpMap();
    void addTerritory(const Territory &t, int ter_num, vector<int> const &);
    void printMap();
    bool isConnected();

};

class continent {

};