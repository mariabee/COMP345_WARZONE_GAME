#include "GameEngine.h"

int main() {
    GameEngine *ge = new GameEngine();
    TournamentModeHandler* t = TournamentModeHandler::fromString("tournament -M canada.map,artic.map,little.map -P aggressive,benevolent,neutral -G 5 -D 50");
    if (t != nullptr) 

    t->run(ge);
    // t->run();
    // GameEngine *ge = new GameEngine();
    // ge->play();
    // delete ge;

    // return 0;
}