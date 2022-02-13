#pragma once
#include <list>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Player;
class Territory {
private:
    int ID, continent_ID, number_of_armies, edge_count;
    string *name;
    Player *player;
    Territory **edges;

public:
    bool visited;
    //CONSTRUCTORS
    Territory();
    Territory(int id, string name, int continentId);
    Territory(const Territory &t);
    Territory& operator=(const Territory& t);
    //DESTRUCTOR
    ~Territory();
    //OVERLOADED << OPERATOR
    friend ostream &operator<<(ostream &os, const Territory &territory);
    //ACCESSORS
        string * getName() const;
        int getId() const;
        int getContinentId() const;
        int getNumberOfArmies() const;
        Player * getOwner() const;
        Territory **getEdges() const;
        int getEdgeCount() const;
    //MUTATORS
        void setId(int id);
        void setName(string name);
        void setContinentId(int continentId);
        void setNumberOfArmies(int numberOfArmies);
        void changeOwner(Player *player_);
    //METHOD TO ADD EDGES TO AN ARRAY OF TERRITORIES
    void addEdges(vector<int> edge_nums, Territory *territories);

};
class Continent {
private:
    int ID, bonus, count, NUM_OF_TERS;
    string *name, *color;
    Territory **subTerritories;
public:
    //CONSTRUCTORS
    Continent();
    Continent(int ID, string name, int bonus, string color);
    Continent(const Continent &c);
    Continent& operator=(const Continent& t);
    //DESTRUCTOR
    ~Continent();
    //METHOD TO INITIALIZE SUBMAP
    void createSubMap(int num_of_ters);
    //METHOD TO ADD TERRITORY LINKS TO SUBMAP
    void addTerritory(Territory *territoryPtr);

    friend ostream &operator<<(ostream &os, const Continent &continent);
    //ACCESSORS
        int getId() const;
        int getBonus() const;
        string * getName() const;
        string * getColor() const;
        int getNumOfTers() const;
        Territory ** getTerritories() const;
    //MUTATORS
        void setId(int id);
        void setName(string name);
        void setBonus(int bonus);
        void setColor(string color);
};

class Map {
    int NUM_OF_TRS, NUM_OF_CNTS;
    bool *visited;
    Territory *territories;
    Continent *continents;
    void visitTerritories(Territory **e, int size, int &count);
    void visitContinent(int id, Territory *t, int &count);
public :
    //CONSTRUCTORS
    Map(Territory territories[], int num_of_trs, Continent continents[], int num_of_cnts);
    Map(const Map &m);
    Map& operator=(const Map& m);
    //DESTRUCTOR
    ~Map();
    //OVERLOADED << OPERATOR
    friend ostream &operator<<(ostream &os, const Map &map);
    //VALIDATE METHOD
    bool validate();
    //ACCESSORS
    int getNumOfTers() const;
    int getNumOfCnts() const;
    Territory *getTerritories() const;
    Continent *getContinents() const;
};

class MapLoader {
private:
    MapLoader();
public:
    static Map loadMap(const string& filename);
};