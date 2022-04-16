#include "GameEngine.h"

int main() {
    auto *ge = new GameEngine();
    ge->play();

    delete ge;
    return 0;
}