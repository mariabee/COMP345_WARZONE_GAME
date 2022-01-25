#include "Orders.h"
#include<iostream>
#include<vector>
#include<bits/stdc++.h>

class OrdersList{
public:
    OrdersList();

    void add(order* o);
    void move(order* o, int position);
    void remove(order* o);
    bool contain(order **o);

    virtual ~OrdersList();

private:
    vector<order*> list;
    vector<order*>::iterator ptr;
};

void OrdersList::add(order* o) {
    list.push_back(o);
}
void OrdersList::move(order* o, int position) {
    auto it = list.begin()+position;
    if(contain(&o)) {
        remove(o);
        list.insert(it, o);
    }
    else{
        cout<<"Order not found";
        return;
    }
}

void OrdersList::remove(order* o) {
    ptr = find(list.begin(), list.end(),o);
    list.erase(ptr);
}

bool OrdersList::contain(order **o) {
    ptr = find(list.begin(), list.end(),*o);
    if (ptr != list.end())
    {
        //WE SHOULD MAKE AN ORDER PRINT FUNCTION FOR DEBUGGING AFTER MAP AND PLAYER
        cout << "Element " << o <<" found at position : " ;
        cout << ptr - list.begin() <<endl;
        ptr = list.begin();
        return true;
    }
    else {
        std::cout << "Element not found.\n\n";
        ptr = list.begin();
        return false;
    }
}

OrdersList::OrdersList(){
    list;
    ptr;
}

OrdersList::~OrdersList() {
    list.clear();
}

//TEMPORARY MAIN METHOD FOR TESTING
int main() {
    OrdersList *testList = new OrdersList();
    Deploy d1;
    Deploy *d = &d1; //Alternative to using new ClassName()
    Advance* a = new Advance();
    Bomb* b = new Bomb();
    Blockade* bl = new Blockade();
    Airlift* ai = new Airlift();
    Negotiate* n = new Negotiate();
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
