#include <iostream>
#include <string>
#include <list> 
using namespace std;

class Order
{
public:
    virtual bool validate() = 0;
    virtual void execute() = 0;
    //Accessors
    string getOrderType() { return orderType; }
    string getOrderEffect() { return orderEffect; }
    //Mutators
    void setOrderType(string _o) { orderType = _o; }
    void setOrderEffect(string effect) { orderEffect = effect; }

private:
    friend ostream& operator<<(ostream&, const Order&);
    string orderType;
    string orderEffect;
};
ostream& operator << (ostream& strm, const Order& orderObj) {

    return strm << orderObj.orderType << endl;
}

//SUBCLASSES 

class Deploy : public Order {
public:
    //Default constructor 
    Deploy() { setOrderType("Deploy"); }

    void execute() {
        if (validate()) {
            setOrderEffect("Troops have been deployed.");
        }
    }
private:
    bool validate() {
        //PLACEHOLDER
        return true;
    }
};
class Advance : public Order {
};
class Bomb : public Order {
};
class Blockade : public Order {
};
class Airlift : public Order {
};
class Negotiate : public Order {
};

int main() {
    list<Order*> testList;
    Deploy* d = new Deploy();
    testList.push_front(d);

}