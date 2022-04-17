#include "GameEngine.h"

int main() {
    GameEngine *ge = new GameEngine();
    TournamentModeHandler* t = TournamentModeHandler::fromString("tournament -M little.map,canada.map,artic.map -P aggressive,benevolent,benevolent -G 5 -D 50");
    if (t != nullptr) {
        // cout << *t;
        t->run(ge);
    } else cout << "bad";
    // t->run();
    // GameEngine *ge = new GameEngine();
    // ge->play();
    // delete ge;

    // return 0;
}