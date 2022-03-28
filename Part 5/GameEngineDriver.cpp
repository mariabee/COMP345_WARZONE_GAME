
#include "./GameEngine.h"
#include "./CommandProcessor.h"
#include <iostream>

using namespace std;

int main()
{
    cout<<"Hello World";
    GameEngine *ge = new GameEngine();
    CommandProcessor cp = new CommandProcessor(ge);
    cp.getCommand();
    ge->start();
    delete ge;

    return 0;
}
