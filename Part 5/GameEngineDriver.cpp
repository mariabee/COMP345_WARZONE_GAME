#include "./GameEngine.h"

int main() {
    TournamentModeHandler* t = TournamentModeHandler::fromString("tournament -M ../Debug/MapFiles/artic.map -P player,cheater -G 5 -D 5");
    if (t != nullptr)
        cout << *t;
    else cout << "bad";
    // t->run();
    // GameEngine *ge = new GameEngine();
    // ge->play();
    // delete ge;

    // return 0;
}