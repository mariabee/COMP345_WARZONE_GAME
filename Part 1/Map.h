#pragma once
#include <list>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Territory {
private:
    int ID, continent_ID, number_of_armies, edge_count;
    string *name;
    Territory *edges;
public:
    void setId(int id);
    void setName(string name);
    void setContinentId(int continentId);
    void setNumberOfArmies(int numberOfArmies);
    string getName() const;
    int getId() const;
    int getContinentId() const;
    int getNumberOfArmies() const;
    void addEdges(vector<int> edge_nums, Territory *territories);
    Territory *getEdges();
    int getEdgeCount() const;
    friend ostream &operator<<(ostream &os, const Territory &territory);
    Territory(int id, string name, int continentId);
    Territory();
    ~Territory();
};
class Map {
    int NUM_OF_TRS;
    bool *visited;
    void countVisited(Territory *t, int &i, int size);
    static void printEdges(Territory *ptr, int i) ;
public :
    Territory *territories;
    Map(Territory territories[], int num_of_trs);
    ~Map();
    void printMap() const;
    bool isConnected();
};
/*
class Territory{
private:
    int ID;
    string *name;
    int continent_ID;
    int number_of_armies;
public:
    void setId(int id);
    void setName(string name);
    void setContinentId(int continentId);
    void setNumberOfArmies(int numberOfArmies);
    string getName() const;
    int getId() const;
    int getContinentId() const;
    int getNumberOfArmies() const;

    friend ostream &operator<<(ostream &os, const Territory &territory);
    Territory(int id, string name, int continentId);
    Territory();
};
struct Node
{
    Territory *value;
    Node* next;
};
struct Edge {
    int src, dest;
};
class Map {
    int NUM_OF_TRS;
    Territory *territories;
    void AppendNode(int dest, Node *head);
    bool *visited;
    int countVisited(Node *ptr, int &i);
    static void printNode(Node *ptr);
public :
    Node **head;
    Map(const vector<Edge>&, Territory territories[], int num_of_trs);
    ~Map();
    void printMap() const;
    bool isConnected();

};*/

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
        //DESTRUCTOR
        ~Continent();
        //ADD TERRITORIES
        void createSubMap(int num_of_ters);
        void addTerritory(Territory &mapLink);

        friend ostream &operator<<(ostream &os, const Continent &continent);
        //ACCESSORS
        int getId() const;
        int getBonus() const;
        string getName() const;
        string getColor() const;
        int getNumOfTers() const;
        int* getTerritoryIDs();
        Territory* getTerritories() const;
        //MUTATORS
        void setId(int id);
        void setName(string name);
        void setBonus(int bonus);
        void setColor(string color);
};

class MapLoader {
private:
    Map *map;
public:
    explicit MapLoader(const string& filename);
    Map getMap() const;
};