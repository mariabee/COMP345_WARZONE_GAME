//MAIN METHOD FOR TESTING
#include "Orders.h"

int main() {
    auto *testList = new OrdersList();
    auto *t1 = new Territory();
    auto *d = new Deploy();
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
    cout << endl << "Making new negotiate object...." << endl;
    auto *n2 = new Negotiate(*n);
    n2->execute();
    cout << *n2 << endl;
    cout << endl << "DELETING LIST AND ALL ORDERS IN IT. " << endl;
    delete testList;
}

