#include "./GameEngine.h"

int main() {
    GameEngine *ge = new GameEngine();
    ge->play();
    delete ge;

    return 0;
}