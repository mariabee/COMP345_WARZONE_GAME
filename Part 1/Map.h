#pragma once
#include <list>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

};

class Continent {
    private:
        int ID;
        string *name;
        int bonus;
        string *color;
        int i;
        int NUM_OF_TERS;
        Node **subTerritories;
    public:
        //CONSTRUCTORS
        Continent();
        Continent(int ID, string name, int bonus, string color);
        //ADD TERRITORIES
        void createSubMap(int num_of_ters);
        void addTerritory(Node &mapLink);

        friend ostream &operator<<(ostream &os, const Continent &continent);
        //ACCESSORS
        int getId() const;
        int getBonus() const;
        string getName() const;
        string getColor() const;
        int getNumOfTers() const;
        int* getTerritoryIDs();
        Node* getTerritoryNodes() const;
        //MUTATORS
        void setId(int id);
        void setName(string name);
        void setBonus(int bonus);
        void setColor(string color);
};

class MapLoader {
private:
    string *str;
    int counter{0};
    vector<string> *continentLine,*countries,*borders;
    vector<Edge> *edges;
    Map *map;
public:
    explicit MapLoader(const string& filename);
    Map getMap() const;
};