/*
//MAIN METHOD FOR TESTING
#include "Orders.h"
#include "../Part 2/Player.h"


int main() {
    auto *testList = new OrdersList();
    auto *t1 = new Territory();
    Player *p1 = new Player("Jane Doe");
    t1->changeOwner(p1);

    auto *d = new Deploy(p1, t1, 5);
    d->setTerritory(t1);
    d->setNumberOfArmies(5);
    auto *a = new Advance();
    auto *b = new Bomb();
    auto *bl = new Blockade();
    auto *ai = new Airlift();
    auto *n = new Negotiate();
    testList->add(d);
    testList->add(b);
    testList->add(bl);
    testList->add(ai);
    testList->add(n);
    testList->add(a);
    cout << "Moving deploy order ...." << endl;
    testList->move(d,5);
    cout << "Seeing if orders list contains deploy ... " << endl;
    testList->contain(d);
    cout << endl << "Removing advance order.... " << endl;
    testList->remove(a);
    cout << "Removing advance order again... " << endl;
    testList->remove(a);
    cout << endl << "Executing orders...." << endl;
    b->execute();
    d->execute();
    bl->execute();
    ai->execute();
    n->execute();
    cout << "Printing list..." << endl;
    cout << *testList << endl;
    cout << endl << "DELETING LIST AND ALL ORDERS IN IT. ";
    delete testList;
}

*/
