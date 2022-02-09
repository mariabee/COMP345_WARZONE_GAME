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
    c->setId(4);
    cout << c->getId() << endl;
    c->setBonus(10);
    cout << c->getBonus() << endl;
    cout << *c << endl;
    cout << Continent(2, "OTHER NAME", 3, "PURPLE") << endl;


    MapLoader mapLoad("../Debug/canada.map");
    Map map = mapLoad.getMap();


        unsigned char M = -1;
        printf ("M in Decimal is: %d\n",M ) ;
        printf ("M in Hexadecimal is: %X\n",M ) ;

        char N =125;
        N = N + 5;
        printf ("N in Decimal is: %d\n",N ) ;
        printf ("N in Hexadecimal is: %X\n",N ) ;



    return 0;
}
