#include "Map.h"
int main() {
    auto *t = new Territory("Canada");
    auto *v = new Territory("US");

    Map *m = new Map(4);
    m->addTerritory(*t, 1, {2, 3});
    m->addTerritory(*t, 2, {1});
    m->addTerritory(*v, 3, {4});
    m->addTerritory(*v, 4, {2});
    m->cleanUpMap();
    m->printMap();
    m->isConnected() ? cout << "CONNECTED" : cout << "NOT CONNECTED";
    delete m;

    return 0;
}
