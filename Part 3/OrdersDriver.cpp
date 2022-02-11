//MAIN METHOD FOR TESTING
#include "Orders.h"

int main() {
    auto *testList = new OrdersList();
    Deploy *d = new Deploy();
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
    testList->add(d);
    testList->move(d,6);
    testList->contain(d);
    testList->remove(a);
    testList->remove(a);

    auto *n2 = new Negotiate(*n);
    n2->execute();
    delete n2;

    cout << "\nTHIS WORKS END";

}

