#include "./GameEngine.h"

int main() {
    GameEngine *ge = new GameEngine();
    ge->startupPhase();
    delete ge;
}