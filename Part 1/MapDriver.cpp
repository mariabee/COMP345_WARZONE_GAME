#include "Map.h"
int main() {
    Map *m = new Map(4);
    m->addBorder(0, 1);
    m->addBorder(0, 2);
    m->addBorder(1, 0);
    m->addBorder(2, 1);
    m->addBorder(2, 0);
    m->addBorder(3, 2);
    m->addBorder(2, 3);
    m->printMap();

}
