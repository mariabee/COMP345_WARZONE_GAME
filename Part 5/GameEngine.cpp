#include <random>
#include <algorithm>
#include <queue>
#include <utility>
#include "GameEngine.h"


// Assignment operator overload for Command
Command &Command::operator=(const Command &c) {
    if (this == &c) return *this;
    delete command;
    delete effect;

    command = new std::string(*c.command);
    effect = new std::string(*c.effect);
    return *this;
}

// Copy constructor for Command
Command::Command(const Command &c) {
    command = new std::string(*c.command);
    effect = new std::string(*c.effect);
}

// Stream insertion operator overload for Command
std::ostream &operator<<(std::ostream &out, const Command &c) {
    out << *c.command;
    return out;
}

void Command::saveEffect(std::string* e) {
    effect = e;
    notify();
}

std::string Command::stringToLog() {
    return "COMMAND::\"" + *effect + "\"";
}

// Destructor for Command
Command::~Command() {
    std::cout << "Deleting command: \"" << *this << "\"" << std::endl;

    delete effect;
    delete command;
}

// Constructor for Command that takes a string
Command::Command(std::string c) {
    command = new std::string(std::move(c));
    effect = new std::string("");
}

// Function that returns a boolean corresponding to whether a given string matches the command
bool Command::matches(const std::string& s) const {
    return *command == s;
}

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
    // std::cout << "Deleting transition" << std::endl;
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
    //std::cout << "Deleting state: \"" << *this << "\"" << std::endl;
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
        currentState = currentState->getTransition(currentState->getCommandIndex(std::move(s)))->getState();
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
void GameEngine::initial_start() {
    std::string input;
    int index;

    while (currentState != states[5]) {
        std::cin >> input;
        if ((index = currentState->getCommandIndex(input)) == -1)
            std::cout << "No command: \"" << input << "\" usable from current state! Currently at state "
                      << (*currentState) << std::endl;
        else {
            currentState = (currentState->getTransition(index))->getState();
            std::cout << "Transition to state: \"" << (*currentState) << "\"" << std::endl;
            startupPhase();
        }
        notify();

    }
}


void GameEngine::startupPhase() {
    std::string input;
    Player *temp_player;
    initializeStrategies();
    initializeDeck();

    if (currentState == states[1]) {
        std::cout << "Enter the map you want to load in the game: " << std::endl;
        std::cin >> input;
        map = new Map(MapLoader::loadMap(dir + input));
        std::cout << "Map " << input << " loaded successfully" << std::endl;
        //               std::cout << map->getTerritories()[2] << std::endl;
    }

    if (currentState == states[2]) {
        if (!map->validate()) {
            std::cout << "Map not valid, please reenter a valid map file" << std::endl;
            currentState = states[0];
        }
    }

    if (currentState == states[3]) {
        int num_of_players;
        std::cout << "Enter the number of players joining the game (2-6): " << std::endl;
        std::cin >> num_of_players;
        if (num_of_players + players.size() > MAX_NUM_PLAYERS) {
            std::cout << "Max number of players reached, failed to add these players!" << std::endl;
        } else {
            for (int i{0}; i < num_of_players; i++) {
                std::cout << "Enter the player's name: " << std::endl;
                std::cin >> input;
                temp_player = new Player(input);
                temp_player->setStrategy(strategies[0]);
                players.push_back(temp_player);
            }
            std::cout << "Players added successfully" << std::endl;
        }
    }

    if (currentState == states[4]) {
        if (players.size() < MIN_NUM_PLAYERS) {
            std::cout << "Not enough players! Waiting for more players to join!" << std::endl;
            currentState = states[3];
        } else {
            distributeTerritories();
//                    std::cout << *(players.at(0)->getTerritories()->at(2)->getName()) << std::endl;
            randomizePlayOrder();
            std::cout << "The order of turn is as follow: ";
            for (int i{0}; i < players.size() - 1; i++)
                std::cout << " || Player " << *(players.at(i)) << " ";
            std::cout << " || Player " << *(players.at(players.size() - 1)) << " || ";
            std::cout << std::endl;
//                    std::cout << *(players.at(0)->getTerritories()->at(2)->getName()) << std::endl;
            for (int i{0}; i < players.size(); i++) {
                players.at(i)->setArmies(50);
                std::cout << "Player " << *(players.at(i)) << " currently has " << players.at(i)->getArmies()
                          << " reserved troops in their inventory." << std::endl;
                std::cout << "Player " << *(players.at(i)) << " will now pick 2 cards from the deck!" << std::endl;
                players.at(i)->getHand()->drawFromDeck(new_deck);
                players.at(i)->getHand()->drawFromDeck(new_deck);
            }
            currentState = states[5];
        }

    }

}


void GameEngine::play() {
    initial_start();
    mainGameLoop();
}

void GameEngine::mainGameLoop() {
    std::cout << "Main Game Loop starting..." << std::endl;
    roundCount = 0;
    do {
        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();
        roundCount++;
    } while (currentState != states[8]);
    string playOrEnd;
    std::cout << "Play or end game?" << std::endl;
    State *previousState = currentState;
    while (currentState == previousState) {
        std::cin >> playOrEnd;
        setState(playOrEnd);
    }
    if (currentState == states[0]) {
        play();
    }
    if (currentState == states[9]) {
        cout << "Thank you for playing! Game is over." << endl;
    }
}

void GameEngine::reinforcementPhase() {
    cout << "Entering reinforcement phase" << endl;
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
    for (auto current_p : players) {
        //get current player
        cout << "CURRENT PLAYER : " << *current_p << endl;
        current_p->issueOrder();
    }
    /*
        int armies = current_p->getArmies();
        if (!toDefend->empty()) {
            int split = armies / (toDefend->size());
            int i = 0;
            if (split == 0) {
                split = 1;
            } else {
                int remain = armies % (toDefend->size());
                if (remain > 0) {
                    current_p->issueOrder(new Deploy(current_p, toDefend->at(0), remain));
                    i = 1;
                }
            }
            while (armies > 0) { //Deploy armies evenly across all the toDefend territories
                current_p->issueOrder(new Deploy(current_p, toDefend->at(i), split)); //at toDefend[i]
                i++;
                if (i == toDefend->size()) {
                    i = 0;
                }
                armies -= split;
            }
        }*/

    setState("endissueorders");
}


void GameEngine::executeOrdersPhase() {
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
        if (!orders->getList()->empty()) {
            //If a player's order's list is not empty, pop it off the top and execute it.
            if (deployRound) {
                deployComplete++;
                cout << endl << "Deploying " << *current_p << "'s troops...." << endl;
                order *o = orders->getList()->back();
                while (!orders->getList()->empty() && dynamic_cast<Deploy *>(o)) {
                    orders->popTop()->execute();
                    o = orders->getList()->back();
                }
                if (deployComplete == players.size()) {
                    cout << endl << "ALL TROOPS DEPLOYED. MOVING TO OTHER ORDERS." << endl;
                    deployRound = false;
                }
            }
            else {
                    orders->popTop()->execute();
            }
        } else {
            skipped++;
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
    if (roundCount == 10) {
        cout << "FORCING WIN BY ASSIGNING ALL TERRITORIES TO PLAYER 1... " << endl;
        for (int i = 0; i < map->getNumOfTers(); i++) {
            players.at(0)->addTerritory(&map->getTerritories()[i]);
        }
    }
    int i = 0;
    for (Player *p: players) {
        if (p->getTerritories()->size() == map->getNumOfTers()) {
            cout << *p->getName() << " has won the game!" << endl;
            setState("win");
            break;
        }
        else if (p->getTerritories()->empty()) {
            players.erase(players.begin() + i);
        }
        i++;
    }
    if (currentState != states[8]) {
        setState("endexecorders");
    }

}

void GameEngine::testPhase() {
    map = new Map(MapLoader::loadMap(dir + "artic.map"));
    map->validate();
    initializeDeck();
    initializeStrategies();
    for (int i{0}; i < 5; i++) {
        auto *temp_player = new Player("TEST" + to_string(i));
        temp_player->setStrategy(strategies[1]);
        players.push_back(temp_player);
    }
    distributeTerritories();
//                    std::cout << *(players.at(0)->getTerritories()->at(2)->getName()) << std::endl;
    randomizePlayOrder();
    std::cout << "The order of turn is as follow: ";
    for (int i{0}; i < players.size() - 1; i++)
        std::cout << " || Player " << *(players.at(i)) << " ";
    std::cout << " || Player " << *(players.at(players.size() - 1)) << " || ";
    std::cout << std::endl;
//                    std::cout << *(players.at(0)->getTerritories()->at(2)->getName()) << std::endl;
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
    mainGameLoop();
}
