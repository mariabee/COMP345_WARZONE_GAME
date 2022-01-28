#pragma once
#include <list>
#include <iostream>
#include <vector>

using namespace std;



class Continent {
private:
    int ID;
    string name;
    int bonus;
    string color;
public:
    int getId() const;

    void setId(int id);

    const string &getName() const;

    void setName(const string &name);

    int getBonus() const;

    void setBonus(int bonus);

    const string &getColor() const;

    void setColor(const string &color);

    Continent(int ID, const string &name, int bonus, const string &color);

    friend ostream &operator<<(ostream &os, const Continent &continent);

};

class Territory{
private:
    int ID;
    string name;
    int continent_ID;
    int number_of_armies;
    Continent *continent;
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
    }


    void setContinent(Continent *continent);

};
struct Node
{
    Territory *value;
    Node* next;
    Node* previous;
};
struct Edge {
    int src, dest;
};

class Map {
    int num_of_trs;
    Territory *territories;
    Node* getNewNode(int dest, Node *head);

public :
    Node **head;
    Map(Edge edges[], Territory territories[], int num_of_trs, int num_of_edges);
    ~Map();
    void printMap();
    void printNode(Node *ptr);

};