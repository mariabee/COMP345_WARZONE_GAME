#pragma once
#include <list>
#include <iostream>
#include <vector>

using namespace std;


class Territory{
private:
    int ID;
    string name;
    int continent_ID;
    int number_of_armies;
public:
    int getId() const;

    void setId(int id);

    const string &getName() const;

    void setName(const string &name);

    int getContinentId() const;

    void setContinentId(int continentId);

    int getNumberOfArmies() const;

    void setNumberOfArmies(int numberOfArmies);

    friend ostream &operator<<(ostream &os, const Territory &territory);

    Territory(int id, const string &name, int continentId);
    Territory() {
        name = "Default";
        ID = -1;
        continent_ID = -1;
        number_of_armies = -1;
    }

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
    int num_of_trs;
    Territory *territories;
    void AppendNode(int dest, Node *head);
    bool *visited;
    int countVisited(Node *ptr, int &i);
public :
    Node **head;
    Map(Edge edges[], Territory territories[], int num_of_trs, int num_of_edges);
    ~Map();
    void printMap();
    void printNode(Node *ptr);
    bool isConnected();

};

class Continent {
private:
    int ID;
    string name;
    int bonus;
    string color;
    int num_within;
    Node **subGraph;
public:
    int getId() const;

    void setId(int id);

    const string &getName() const;

    void setName(const string &name);

    int getBonus() const;

    void setBonus(int bonus);

    const string &getColor() const;

    void setColor(const string &color);

    int getTerritoryID(int i );
    Territory getTerritory(int i);

    Continent(int ID, const string &name, int bonus, const string &color);
    void addTerritories(const int IDs[], int num_of_trs, Node *mapLinks[]);

    friend ostream &operator<<(ostream &os, const Continent &continent);

};