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
    Continent c2;
    Continent *c = &c2;
    c->setName("TEST");
    cout << c->getName() << endl;
    c->setColor("BLUE");
    cout << c->getColor() << endl;

    MapLoader mapLoad("../Debug/canada.map");
    Map map = mapLoad.getMap();
    map.printMap();


    return 0;
}
