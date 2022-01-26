#pragma once
#include <list>
#include <iostream>
#include <vector>

using namespace std;
class Territory {
    int ID; //id of the country
    int number; //nbr of troops on the territory
    string name; //the name of the country
    string continent; //the continent it belongs to (discuss if we should implement continent class
    //Player player; the player that owns the territory
public:
    Territory();
    Territory(const int &ID,const int &number, const string &name, const string &continent);
    ~Territory();

    int getId() const;

    void setId(int id);

    int getNumber() const;

    void setNumber(int number);

    const string &getName() const;

    void setName(const string &name);

    const string &getContinent() const;

    void setContinent(const string &continent);

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