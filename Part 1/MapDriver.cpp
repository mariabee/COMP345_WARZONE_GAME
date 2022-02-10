#include <fstream>
#include "Map.h"

int main() {
    auto *t = new Territory();
    t->setId(1);
    cout << t->getId() << endl;
    t->setName("TEST NAME");
    cout << t->getName() << endl;
    t->setContinentId(1);
    cout << t->getContinentId() << endl;
    t->setNumberOfArmies(4);
    cout << t->getNumberOfArmies() << endl;
    auto *t2 = new Territory(*t);
    cout << t2->getName() << endl;
    delete t, t2;

    Continent *c = new Continent();
    c->setName("TEST CONTINENT");
    cout << c->getName() << endl;
    c->setColor("BLUE");
    cout << c->getColor() << endl;
    c->setId(4);
    cout << c->getId() << endl;
    c->setBonus(10);
    cout << c->getBonus() << endl;
    cout << *c << endl;
    cout << Continent(2, "OTHER NAME", 3, "PURPLE") << endl;
    Map *map = new Map(MapLoader::loadMap("../Debug/canada.map"));
    if (!map->validate()) {
        cout << "MAP IS NOT VALID";
    }
    else {
        cout << "MAP IS VALID";
    }
    delete map;




    return 0;
}
