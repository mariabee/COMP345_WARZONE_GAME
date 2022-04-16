#include <random>
#include <algorithm>
#include <queue>
#include <utility>
#include "GameEngine.h"

// Assignment operator overload for Transition
Transition &Transition::operator=(const Transition &t) {
    if (this == &t) {return *this; }
    delete on;
    from = t.from;
    to = t.to;
    on = new Command(*t.on);
    return *this;
}

// Copy constructor for Transition
Transition::Transition(const Transition &t) {
    from = t.from;
    to = t.to;
    on = new Command(*t.on);
}

// Constructor for Transtion that takes two states one start and one destination,
// and a string corresponding to the command that transitions between them
Transition::Transition(State *f, State *t, std::string o) {
    from = f;
    to = t;
    on = new Command(move(o));
}

// Stream insertion operator overload for Transition
std::ostream &operator<<(std::ostream &out, const Transition &t) {
    out << *t.from << " =" << *t.on << "=> " << *t.to;
    return out;
}

// Destructor for Transition
Transition::~Transition() {
    std::cout << "Deleting transition" << std::endl;
    delete on;
}

// Function that returns the State corresponding to the destination of the transition
State *Transition::getState() {
    return to;
}


// Function that returns a boolean corresponding to whether the string matches the current transition's command
bool Transition::matches(const std::string& s) {
    return on->matches(s);
}

// Assignment operator overload for State
State &State::operator=(const State &s) {
    if (this == &s) return *this;
    for (int i = 0; i < index; i++)
        delete transitions[i];
    delete[] transitions;

    index = s.index;
    name = new std::string(*s.name);
    transitions = new Transition *[s.index];
    for (int i = 0; i < index; i++)
        transitions[i] = new Transition(*s.transitions[i]);

    return *this;
}

// Copy constructor for State
State::State(const State &s) {
    index = s.index;
    name = new std::string(*s.name);
    transitions = new Transition *[s.index];
    for (int i = 0; i < index; i++)
        transitions[i] = new Transition(*s.transitions[i]);
}

// Constructor for State that takes in a name
State::State(std::string n) {
    name = new std::string(std::move(n));
}

// Stream insertion operator overload for State
std::ostream &operator<<(std::ostream &out, const State &s) {
    out << *s.name;
    return out;
}

std::string& State::toString() const {
    return *name;
}

// Destructor for State
State::~State() {
    std::cout << "Deleting state: \"" << *this << "\"" << std::endl;
    for (int i = 0; i < index; i++)
        delete transitions[i];
    delete[] transitions;

}

// Function that returns true if the state is an end state and false otherwise
bool State::isEnd() const {
    return *name == END_STATE;
}

// Function that the index of the command given, if none match it returns -1
int State::getCommandIndex(const std::string& s) {
    for (int i = 0; i < index; i++) {
        if (transitions[i]->matches(s))
            return i;
    }
    return -1;
}

void GameEngine::setState(const std::string& s) {
    int index = currentState->getCommandIndex(s);
    if (index == -1) {
        std::cout << "No command: \"" << s << "\" usable from current state! Currently at state "
                  << (*currentState) << std::endl;
    }
    else {
        currentState = currentState->getTransition(currentState->getCommandIndex(s))->getState();
        std::cout << "Transition to state: \"" << (*currentState) << "\"" << std::endl;
    }
    notify();
}

// Function that returns a transition at a certain stored index
Transition *State::getTransition(int i) {
    return transitions[i];
}

// Funciton that allows setting a transition for a state
void State::setTransitions(Transition *t) {
    transitions[index++] = t;
}

// Assignment operator overload for GameEngine
GameEngine &GameEngine::operator=(const GameEngine &ge) {
    if (this == &ge) return *this;
    for (int i = 0; i < stateCount; i++)
        delete states[i];
    delete states;

    stateCount = ge.stateCount;
    for (int i = 0; i < stateCount; i++)
        states[i] = new State(*ge.states[i]);

    currentState = new State(*ge.currentState);

    return *this;
}

// Copy constructor for GameEngine
GameEngine::GameEngine(const GameEngine &ge) {
    map = ge.map;
    strategies = ge.strategies;
    new_deck = ge.new_deck;
    gameOver = ge.gameOver;
    stateCount = ge.stateCount;
    states = new State*[10];
    for (int i = 0; i < stateCount; i++)
        states[i] = new State(*ge.states[i]);

    currentState = new State(*ge.currentState);
}

// Default constructor for GameEngine
GameEngine::GameEngine() {
    gameOver = false;
    strategies = nullptr;
    map = nullptr;
    build();
}

// Stream insertion operator overload for GameEngine
std::ostream &operator<<(std::ostream &out, const GameEngine &ge) {
    out << ge.currentState;
    return out;
}

// Destructor for GameEngine
GameEngine::~GameEngine() {
    for (int i = 0; i < stateCount; i++) {
        delete states[i];
    }
    cout << "DELETED STATES " << endl;
    delete states;
    cout << "DELETED STATES POINTER " << endl;
    delete new_deck;
    cout << "DELETED DECK " << endl;
    players.clear();
    cout << "DELETED PLAYERS " << endl;
    delete map;
    cout << "DELETED MAP" << endl;
}

std::string GameEngine::stringToLog() {
    return "GameEngine::Transitioning to state: " + currentState->toString();
}

void GameEngine::distributeTerritories() {
    size_t num_of_ter = map->getNumOfTers();
    size_t num_of_player = players.size();
    size_t start_index{0};
    size_t end_index{0};
    size_t divide = num_of_ter / num_of_player;
    size_t remain = num_of_ter % num_of_player;


    for (int i{0}; i < num_of_player; i++) {
        auto *t = new vector<Territory *>();
        if (remain == 0) {
            end_index = start_index + divide;
        } else {
            end_index = start_index + divide + 1;
            remain--;
        }
        for (size_t j = start_index; j < end_index; j++) {
            Territory *ter = &map->getTerritories()[j];
            t->push_back(ter);
        }
        players.at(i)->setTerritories(t);
        start_index = end_index;
    }
}

void GameEngine::randomizePlayOrder() {
    default_random_engine randEngine{random_device{}()};
    shuffle(players.begin(), players.end(), randEngine);
}

void GameEngine::initializeDeck() {
    new_deck = new Deck(100);
}
void GameEngine::initializeStrategies() {
    strategies = new PlayerStrategy*[5];
    strategies[0] = new HumanPlayerStrategy();
    strategies[1] = new AggressivePlayerStrategy();
    strategies[2] = new BenevolentPlayerStrategy();
    strategies[3] = new NeutralPlayerStrategy();
    strategies[4] = new CheaterPlayerStrategy();
    PlayerStrategy::addDeck(new_deck);
    PlayerStrategy::addPlayers(&players);
}

// Function that builds the transition graph corresponding to the game engine, game state and commands.
void GameEngine::build() {

    auto start = new State(START_STATE);
    currentState = start;
    auto map_load = new State("map_loaded");
    auto map_valid = new State("map_validated");
    auto players_added = new State("players_added");
    auto game_start = new State("game_start");
    auto assign_reinforcement = new State("assign_reinforcement");
    auto issue_orders = new State("issue_orders");
    auto execute_orders = new State("execute_orders");
    auto win = new State("win");
    auto end = new State(END_STATE);
    states = new State *[10]
            {start, map_load, map_valid, players_added, game_start, assign_reinforcement, issue_orders, execute_orders,
             win, end};
    stateCount = 10;

    start->setTransitions(new Transition(start, map_load, "loadmap"));
    map_load->setTransitions(new Transition(map_load, map_load, "loadmap"));
    map_load->setTransitions(new Transition(map_load, map_valid, "validatemap"));
    map_valid->setTransitions(new Transition(map_valid, players_added, "addplayer"));
    players_added->setTransitions(new Transition(players_added, players_added, "addplayer"));
    players_added->setTransitions(new Transition(players_added, game_start, "gamestart"));
    game_start->setTransitions(new Transition(game_start, assign_reinforcement, "assignarmies"));
    assign_reinforcement->setTransitions(new Transition(assign_reinforcement, issue_orders, "issueorder"));
    issue_orders->setTransitions(new Transition(issue_orders, issue_orders, "issueorder"));
    issue_orders->setTransitions(new Transition(issue_orders, execute_orders, "endissueorders"));
    execute_orders->setTransitions(new Transition(execute_orders, execute_orders, "execorder"));
    execute_orders->setTransitions(new Transition(execute_orders, assign_reinforcement, "endexecorders"));
    execute_orders->setTransitions(new Transition(execute_orders, win, "win"));
    win->setTransitions(new Transition(win, start, "play"));
    win->setTransitions(new Transition(win, end, "end"));
}

// Function that starts the game engine, which waits for player input.
void GameEngine::initial_start(CommandProcessor *cp) {
    int index;
    cp->getCommand();
    vector<Command *> *commands = cp->getCommandList();

    while (currentState != states[5]) {
        if (!commands->empty()) {
            Command *c = commands->front();
            index = currentState->getCommandIndex(*c->command);
            if (!CommandProcessor::validate(*c, this)) {
                std::cout << "No command: \"" << *c->command << "\" usable from current state! Currently at state "
                          << (*currentState) << std::endl;
                cp->resetCommandList();
            } else {
                currentState = (currentState->getTransition(index))->getState();
                auto *effect = new string("Transition to state : \"" + *currentState->name  + "\"");
                c->saveEffect(effect);
                startupPhase(c, commands);
            }
        }
        else {
            cp->resetCommandList();
            cp->getCommand();
            commands = cp->getCommandList();
        }

    }
}


void GameEngine::startupPhase(Command *c, vector<Command *> *commands) {
    Player *temp_player;
    if (currentState == states[1]) {
        commands->erase(commands->begin());
        c = commands->front();
        map = new Map(MapLoader::loadMap(dir + *c->command));
        std::cout << "Map " << *c->command << " loaded successfully" << std::endl;
        c->saveEffect(new string("Map loaded successfully."));
        //               std::cout << map->getTerritories()[2] << std::endl;
    }

    if (currentState == states[2]) {
        if (!map->validate()) {
            std::cout << "Map not valid, please reenter a valid map file" << std::endl;
            c->saveEffect(new string("Map file not valid."));
            currentState = states[0];
        }
    }

    if (currentState == states[3]) {
        commands->erase(commands->begin());
        c = commands->front();
        int num_of_players;
        try {
            num_of_players = std::stoi(*c->command);
        }
        catch(std::invalid_argument& e){
            c->saveEffect(new string("Invalid integer entered for number of players."));
            return;
        }
        if (num_of_players + players.size() > MAX_NUM_PLAYERS) {
            std::cout << "Max number of players reached, failed to add these players!" << std::endl;
            c->saveEffect(new string("Max number of players reached, failed to add these players!"));
        } else {
            initializeDeck();
            initializeStrategies();
            for (int i{0}; i < num_of_players; i++) {
                commands->erase(commands->begin());
                if (!commands->empty()) {
                    c = commands->front();
                    temp_player = new Player(*c->command);
                    temp_player->setStrategy(strategies[3]);
                    players.push_back(temp_player);
                }
            }
            players.back()->setStrategy(strategies[4]);
            std::cout << "Players added successfully" << std::endl;
            c->saveEffect(new string("Players added successfully."));
        }
    }

    if (currentState == states[4]) {
        if (players.size() < MIN_NUM_PLAYERS) {
            std::cout << "Not enough players! Waiting for more players to join!" << std::endl;
            currentState = states[3];
        } else {
            distributeTerritories();
            randomizePlayOrder();
            std::cout << "The order of turn is as follow: ";
            for (int i{0}; i < players.size() - 1; i++)
                std::cout << " || Player " << *(players.at(i)) << " ";
            std::cout << " || Player " << *(players.at(players.size() - 1)) << " || ";
            std::cout << std::endl;
            for (int i{0}; i < players.size(); i++) {
                players.at(i)->setArmies(50);
                std::cout << "Player " << *(players.at(i)) << " currently has " << players.at(i)->getArmies()
                          << " reserved troops in their inventory." << std::endl;
                std::cout << "Player " << *(players.at(i)) << " will now pick 2 cards from the deck!" << std::endl;
                players.at(i)->getHand()->drawFromDeck(new_deck);
                players.at(i)->getHand()->drawFromDeck(new_deck);
                cout << *players.at(i)->getHand() << endl;
            }
            currentState = states[5];
        }
    }
    commands->erase(commands->begin());
}


void GameEngine::play() {
    auto *cp = new CommandProcessor();
    initial_start(cp);
    mainGameLoop(cp);
}

void GameEngine::mainGameLoop(CommandProcessor *cp) {
    while (currentState != states[8]) {
        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();
    }
    string playOrEnd;
    vector<Command *> *commands = cp->getCommandList();
    State *previousState = currentState;
    commands = cp->getCommandList();

    while (currentState == previousState) {
        if (commands->empty()) {
            cp->getCommand();
        }
        Command *c = commands->front();
        setState(*c->command);
        commands->erase(commands->begin());
    }
    if (currentState == states[0]) {
        play();
    }
    if (currentState == states[9]) {
        cout << "Thank you for playing! Game is over." << endl;
    }
}

void GameEngine::reinforcementPhase() {
    map->checkContinentOwners();
    int n;
    //Go through every player
    for (Player *p: players) {
        cout << endl << *p << " currently holds : " << p->getTerritories()->size() << " out of ";
        cout << map->getNumOfTers() << " territories." << endl;
        //Reset flags in player
        p->setCardWon(false);
        p->clearCannotAttack();
        //Calculate reinforcement pool and give it to the player.
        n = p->getArmies();
        n += p->getTerritories()->size() / 3;
        for (Continent *c: *p->getContinents()) {
            n += c->getBonus();
        }
        if (n < 3) {
            n = 3;
        }
        p->setArmies(n);
        cout << *p << " has currently " << n << " armies available to deploy. " << endl;
    }
}

void GameEngine::issueOrdersPhase() {
    setState("issueorder");
    std::cout << "Entering the issue orders phase. " << std::endl;
    //Go through each player
    int i = 0;
    for (auto current_p : players) {
        //get current player
        cout << "CURRENT PLAYER : " << *current_p << endl;
        current_p->issueOrder();
        i++;
    }
    setState("endissueorders");
    checkWinner();
}


void GameEngine::executeOrdersPhase() {
    if (currentState == states[7]) {
        int skipped;
        int current = 0;
        bool deployRound = true;
        int deployComplete = 0;
        //Until there are no more orders to be executed...
        while (true) {
            //Players execute orders round robin.
            if (current == 0) {
                skipped = 0;
            }
            Player *current_p = players.at(current);
            OrdersList *orders = current_p->getOrdersList();
            deployComplete++;
            if (orders && !orders->getList()->empty()) {
                //If a player's order's list is not empty, pop it off the top and execute it.
                if (deployRound) {
                    cout << endl << "Deploying " << *current_p << "'s troops...." << endl;
                    order *o = orders->getList()->back();
                    while (!orders->getList()->empty() && dynamic_cast<Deploy *>(o)) {
                        orders->popTop()->execute();
                        o = orders->getList()->back();
                    }
                } else {
                    orders->popTop()->execute();
                }
            } else {
                skipped++;
            }
            if (deployComplete == players.size()) {
                cout << endl << "ALL TROOPS DEPLOYED. MOVING TO OTHER ORDERS." << endl;
                deployRound = false;
            }
            if (skipped == players.size()) {
                //If all the players have skipped, phase is over and return true
                break;
            }
            current++;
            if (current == players.size()) {
                current = 0;
            }
        }
        cout << endl;
        //If player owns all the Territories, the game over.
    }
    if (currentState != states[8]) {
        checkWinner();
    }
    if (currentState == states[7]) {
        setState("endexecorders");
    }
}
void GameEngine::checkWinner() {
    int i = 0;
    for (Player *p: players) {
        if (p->getTerritories()->size() == map->getNumOfTers()) {
            cout << *p->getName() << " has won the game!" << endl;
            setState("win");
        }
        else if (p->getTerritories()->empty()) {
            if (currentState != states[8]) {
                cout << *p->getName() << " has lost the game." << endl;
            }
            players.erase(players.begin() + i);
        }
        i++;
    }
}

void GameEngine::testPhase() {
    map = new Map(MapLoader::loadMap(dir + "artic.map"));
    map->validate();
    initializeDeck();
    initializeStrategies();
    auto *cheat_player = new Player("CHEATER");
    cheat_player->setStrategy(strategies[4]);
    players.push_back(cheat_player);
    auto *neutral_player = new Player("NEUTRAL");
    neutral_player->setStrategy(strategies[3]);
    players.push_back(neutral_player);
    /*auto *benevolent_player = new Player("BENEVOLENT");
    benevolent_player->setStrategy(strategies[2]);
    players.push_back(benevolent_player);
    auto *aggressive_player = new Player("AGGRESSIVE");
    aggressive_player->setStrategy(strategies[1]);
    players.push_back(aggressive_player);
    auto *human_player = new Player("AGGRESSIVE" + to_string(2));
    human_player->setStrategy(strategies[1]);
    players.push_back(human_player);*/

    distributeTerritories();
    randomizePlayOrder();
    std::cout << "The order of turn is as follow: ";
    for (int i{0}; i < players.size() - 1; i++)
        std::cout << " || Player " << *(players.at(i)) << " ";
    std::cout << " || Player " << *(players.at(players.size() - 1)) << " || ";
    std::cout << std::endl;
    for (int i{0}; i < players.size(); i++) {
        players.at(i)->setArmies(50);
        std::cout << "Player " << *(players.at(i)) << " currently has " << players.at(i)->getArmies()
                  << " reserved troops in their inventory." << std::endl;
        std::cout << "Player " << *(players.at(i)) << " will now pick 2 cards from the deck!" << std::endl;
        players.at(i)->getHand()->drawFromDeck(new_deck);
        players.at(i)->getHand()->drawFromDeck(new_deck);
    }
    currentState = states[1];
    currentState = states[2];
    currentState = states[3];
    currentState = states[4];
    currentState = states[5];
    auto *cp = new CommandProcessor();
    mainGameLoop(cp);
}


std::string TournamentModeHandler::stringToLog() {

    return "Test";
}
TournamentModeHandler& TournamentModeHandler::operator=(const TournamentModeHandler &t) {

}
TournamentModeHandler::TournamentModeHandler(const TournamentModeHandler &t) {

}

TournamentModeHandler::TournamentModeHandler() {

}
std::ostream& operator<< (std::ostream &out, const TournamentModeHandler &t) {
    out << "Test";
    return out;

}
TournamentModeHandler::~TournamentModeHandler() {

}

bool isNum(std::string* s) {
    for(auto c:*s)
        if (!isdigit(c)) return false;
    return true;
}

std::string** split(std::string s, char del, int& outCt) {
    std::string** out;
    std::string cur;

    int ct = 1;
    for(auto c:s) {
        if (c == del)
            ct++;
    }
    outCt = ct;
    out = new std::string*[ct];
    // cout << ct;


    int i = 0;
    for(auto c:s) {
        if (c == del) {
            // cout << cur << endl;
            out[i++] = new std::string(cur);
            cur = "";
        } else
            cur += c;
    }
    if (cur.size() > 0) {
        // cout << cur << endl;
        out[i++] = new std::string(cur);
        cur = "";
    }
    
    return out;
}

// std::string** getList(std::string list) {
//     int words = 0;
//     std::string** words = split(list, ',', words);
//     if (wor)
// }

TournamentModeHandler* TournamentModeHandler::fromString(std::string s) {
    // TournamentModeHandler* out = new T

    // TODO: make sure memory is clean before returning nullptr

    int wordCt;
    std::string** words = split(s, ' ', wordCt);
    cout << wordCt;

    // for(int i = 0; i < wordCt; i++) {
    //     if ()
    // }
    if (wordCt != 9) return nullptr;
    if (*words[0] != "tournament") return nullptr;
    if (*words[1] != "-M") return nullptr;
    // if (isNum(words[2])) return nullptr;
    // int subWords = -1;
    // if (subWords == 0)
    if ((*words[2]).size() == 0) return nullptr;
    int m = 0;
    std::string** mapNames = split(*words[2], ',', m);
    Map** oMaps = new Map*[m];
    for(int i =0;i<m;i++) {
        // TODO: if file doesn't exist return nullptr
        // Parse, load and validate map
        oMaps[i] = new Map(MapLoader::loadMap(*mapNames[i]));
        if (!oMaps[i]->validate()) return nullptr;
        delete mapNames[i];
    }
    delete mapNames;

    if (*words[3] != "-P") return nullptr;

    if ((*words[4]).size() == 0) return nullptr;
    int p = 0;
    std::string** playerNames = split(*words[4], ',', m);
    PlayerStrategy** oPS = new PlayerStrategy*[m];
    for(int i =0;i<p;i++) {
        // TODO: if file doesn't exist return nullptr
        // Parse, load and validate player
        // oPS[i] = ;
        delete playerNames[i];
    }
    delete playerNames;

    if (*words[5] != "-G") return nullptr;
    if (!isNum(words[6])) return nullptr;
    if (*words[7] != "-D") return nullptr;
    if (!isNum(words[8])) return nullptr;



    // if (words[])
        
        // cout << *words[i];
    

    return new TournamentModeHandler(oMaps, m, oPS, p, stoi(*words[6]), stoi(*words[8]));
}

TournamentModeHandler::TournamentModeHandler(Map** m, int mapCt, PlayerStrategy** ps, int stratCt, int nGames, int mTurns) {
    maps = m;
    numMaps = mapCt;
    playerStrategies = ps;
    numStrats = stratCt;
    numGames = nGames;
    maxTurns = mTurns;
}

void TournamentModeHandler::run(GameEngine* ge) {
    std::string** winners = new std::string*[numGames];

    for(int i = 0; i < numGames; i++) {
        winners[i] = new std::string[numMaps];
        for(int j = 0; j < numMaps; j++) {
            winners[i][j] = this->playGame(ge, maps[j], playerStrategies, numStrats);
        }
    }


}


std::string TournamentModeHandler::playGame(GameEngine* ge, Map* map, PlayerStrategy** players, int p) {

}