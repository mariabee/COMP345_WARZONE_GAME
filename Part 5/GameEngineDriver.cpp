#include "./GameEngine.h"

int main() {
    GameEngine *ge = new GameEngine();
    ge->start();
    delete ge;
    //state 5 reinforcement
    //state 6 issueorders
    //state 7 executeorders
}