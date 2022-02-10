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
    //CONSTRUCTORS
    Territory(int id, string name, int continentId);
    Territory();
    Territory(const Territory &t);
    Territory& operator=(const Territory& t);
    ~Territory();
    void setId(int id);
    void setName(string name);
    void setContinentId(int continentId);
    void setNumberOfArmies(int numberOfArmies);
    void changeOwner(Player &player);
    //ACCESSORS
    string getName() const;
    int getId() const;
    int getContinentId() const;
    int getNumberOfArmies() const;
    Player getOwner() const;
    void addEdges(vector<int> edge_nums, Territory *territories);
    Territory **getEdges() const;
    int getEdgeCount() const;
    friend ostream &operator<<(ostream &os, const Territory &territory);

};
class Map {
    int NUM_OF_TRS;
    bool *visited;
    void countVisited(Territory **t, int &i, int size);
    static void printEdges(Territory **ptr, int i) ;
public :
    Territory *territories;
    Map(Territory territories[], int num_of_trs);
    Map(const Map &m);
    ~Map();
    void printMap() const;
    bool validate();

    //ACCESSORS
    int getNumOfTers() const;
    Territory *getTerritories() const;
};

class Continent {
    private:
        int ID;
        string *name;
        int bonus;
        string *color;
        int i;
        int NUM_OF_TERS;
        Territory **subTerritories;
    public:
        //CONSTRUCTORS
        Continent();
        Continent(int ID, string name, int bonus, string color);
        Continent(const Continent &c);
        //DESTRUCTOR
        ~Continent();
        //ADD TERRITORIES
        void createSubMap(int num_of_ters);
        void addTerritory(Territory *mapLink);

        friend ostream &operator<<(ostream &os, const Continent &continent);
        //ACCESSORS
        int getId() const;
        int getBonus() const;
        string getName() const;
        string getColor() const;
        int getNumOfTers() const;
        Territory ** getTerritories() const;
        //MUTATORS
        void setId(int id);
        void setName(string name);
        void setBonus(int bonus);
        void setColor(string color);
};

class MapLoader {
private:
    MapLoader();
public:
    static Map loadMap(const string& filename);
};