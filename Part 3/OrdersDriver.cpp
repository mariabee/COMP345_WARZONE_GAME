//MAIN METHOD FOR TESTING
#include "Orders.h"

int main() {
    auto *testList = new OrdersList();
    Deploy d1;
    Deploy *d = &d1; //Alternative to using new ClassName()
    auto *a = new Advance();
    cout << "A VALUE.. " << *a;
    auto *b = new Bomb();
    cout << "B VALUE.. " << *b;
    auto *bl = new Blockade();
    cout << "BL VALUE.. " << *bl;
    auto *ai = new Airlift();
    cout << "AI VALUE.. " << *ai;
    auto *n = new Negotiate();
    cout << "N VALUE.. " << *n;
    n->set_order_effect("TESTING ORDER EFFECT");
    cout << *n;

    testList->add(d);
    testList->add(a);
    testList->add(b);
    testList->add(bl);
    testList->add(ai);
    testList->add(n);
    testList->remove(b);
    testList->move(d,2);
    cout << "\nTHIS WORKS END";


}

