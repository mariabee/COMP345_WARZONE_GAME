#pragma once
#include <string>
#include <iostream>
using namespace std;

//BASE CLASS 
class order {
	public:
        order(); 
        order(const order& other); 
        virtual ~order(); 
        virtual bool validate() = 0;
        virtual void execute() = 0; 
        //Accessors
        string get_order_type() const;
        string get_order_effect() const;
        //Mutators
        void set_order_type(string order);
        void set_order_effect(string effect);

    private:
        friend ostream& operator<<(ostream&, const order&);
        string* order_type_;
        string* order_effect_;
};

//SUBCLASSES - TYPES OF ORDERS 

class Deploy : public order {
    public:
        //Default constructor 
        Deploy();
        void execute() override;
    private:
        bool validate() override;
};
class Advance : public order {
    public:
        //Default constructor 
        Advance();
        void execute() override;
    private:
        bool validate() override;
};
class Bomb : public order {
    public:
        //Default constructor 
        Bomb();
        void execute() override;
    private:
        bool validate() override;
};
class Blockade : public order {
    public:
        //Default constructor 
        Blockade(); 
        void execute() override;
    private:
        bool validate() override;
};
class Airlift : public order {
    public:
        //Default constructor 
        Airlift();
        void execute() override;
    private:
        bool validate() override;
};
class Negotiate : public order {
    public:
        Negotiate(); 
        void execute() override;
    private:
        bool validate() override;
};
