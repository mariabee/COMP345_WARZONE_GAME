#include <random>
#include <algorithm>
#include "GameEngine.h"


// Assignment operator overload for Command
Command& Command::operator=(const Command &c)
{
	delete command;

	command = new std::string(*c.command);
	return *this;
}

// Copy constructor for Command
Command::Command(const Command &c)
{
	command = new std::string(*c.command);
}

// Stream insertion operator overload for Command
std::ostream& operator<< (std::ostream &out, const Command &c) {
	out << *c.command;
	return out;
}

// Destructor for Command
Command::~Command()
{
	//std::cout << "Deleting command: \"" << *this << "\"" << std::endl;
}

// Constructor for Command that takes a string
Command::Command(std::string c)
{
	command = new std::string(c);
}

// Function that returns a boolean corresponding to whether a given string matches the command
bool Command::matches(std::string s)
{
	return *command == s;
}

// Assignment operator overload for Transition
Transition& Transition::operator=(const Transition &t)
{
	delete on;

	from = t.from;
	to = t.to;
	on = new Command(*t.on);

	return *this;
}

// Copy constructor for Transition
Transition::Transition(const Transition &t)
{
	from = t.from;
	to = t.to;
	on = new Command(*t.on);
}

// Constructor for Transtion that takes two states one start and one destination,
// and a string corresponding to the command that transitions between them
Transition::Transition(State *f, State *t, std::string o)
{
	from = f;
	to = t;
	on = new Command(o);
}

// Stream insertion operator overload for Transition
std::ostream& operator<< (std::ostream &out, const Transition &t) {
	out << *t.from << " =" << *t.on << "=> " << *t.to;
	return out;
}

// Destructor for Transition
Transition::~Transition()
{
	// std::cout << "Deleting transition" << std::endl;
	delete on;
}

// Function that returns the State corresponding to the destination of the transition
State *Transition::getState()
{
	return to;
}

// Function that returns a boolean corresponding to whether the string matches the current transition's command
bool Transition::matches(std::string s)
{
	return on->matches(s);
}

// Assignment operator overload for State
State& State::operator=(const State &s)
{
	for (int i = 0; i < index; i++)
		delete transitions[i];
	delete transitions;
	delete acceptedCommands;

	acceptedCommands = new Command(*s.acceptedCommands);
	index = s.index;
	name = new std::string(*s.name);
	transitions = new Transition*[s.index];
	for (int i =0; i<index; i++)
		transitions[i] = new Transition(*s.transitions[i]);

	return *this;
}

// Copy constructor for State
State::State(const State &s)
{
	acceptedCommands = new Command(*s.acceptedCommands);
	index = s.index;
	name = new std::string(*s.name);
	transitions = new Transition*[s.index];
	for (int i =0; i<index; i++)
		transitions[i] = new Transition(*s.transitions[i]);
}

// Constructor for State that takes in a name
State::State(std::string n)
{
	name = new std::string(n);
}

// Stream insertion operator overload for State
std::ostream& operator<< (std::ostream &out, const State &s) {
	out << *s.name;
	return out;
}

// Destructor for State
State::~State()
{
	//std::cout << "Deleting state: \"" << *this << "\"" << std::endl;
	for (int i = 0; i < index; i++)
		delete transitions[i];
	delete transitions;
	delete acceptedCommands;
}

// Function that returns true if the state is an end state and false otherwise
bool State::isEnd() {
	return *name == END_STATE;
}

// Function that the index of the command given, if none match it returns -1
int State::getCommandIndex(std::string s)
{
	for (int i = 0; i < index; i++)
	{
		if (transitions[i]->matches(s))
			return i;
	}
	return -1;
}

// Function that returns a transition at a certain stored index
Transition *State::getTransition(int i)
{
	return transitions[i];
}

// Funciton that allows setting a transition for a state
void State::setTransitions(Transition *t)
{
	transitions[index++] = t;
}

// Assignment operator overload for GameEngine
GameEngine& GameEngine::operator=(const GameEngine &ge)
{
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
GameEngine::GameEngine(const GameEngine &ge)
{
	stateCount = ge.stateCount;
	for (int i = 0; i < stateCount; i++)
		states[i] = new State(*ge.states[i]);

	currentState = new State(*ge.currentState);
}

// Default constructor for GameEngine
GameEngine::GameEngine()
{
    gameOver = false;
	build();
}

// Stream insertion operator overload for GameEngine
std::ostream& operator<< (std::ostream &out, const GameEngine &ge) {
	out << ge.currentState;
	return out;
}

// Destructor for GameEngine
GameEngine::~GameEngine()
{
	for (int i = 0; i < stateCount; i++)
		delete states[i];
	delete states;
}

void GameEngine::distributeTerritories() {
    size_t num_of_ter = map->getNumOfTers();
    size_t num_of_player = players.size();
    size_t start_index {0};
    size_t end_index {0};
    size_t divide = num_of_ter / num_of_player;
    size_t remain = num_of_ter % num_of_player;


    for (int i{0}; i < num_of_player; i++) {
        auto *t = new vector<Territory*>();
        if (remain == 0) {
            end_index = start_index + divide;
        } else {
            end_index = start_index + divide + 1;
            remain--;
        }
        for (size_t j = start_index; j < end_index; j++) {
            auto* ter = new Territory(map->getTerritories()[j]);
            t->push_back(ter);
        }
        players.at(i)->setTerritories(t, (int)t->size());
        start_index = end_index;
    }
}

void GameEngine::randomizePlayOrder()
{
    default_random_engine randEngine{random_device{}()};
    shuffle(players.begin(), players.end(), randEngine);
}

void GameEngine::initializeDeck()
{
    new_deck = new Deck(100);
}


// Function that builds the transition graph corresponding to the game engine, game state and commands.
void GameEngine::build()
{

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
	{ start, map_load, map_valid, players_added, game_start, assign_reinforcement, issue_orders, execute_orders, win, end };
	stateCount = 10;

	start->setTransitions(new Transition(start, map_load, "loadmap"));
	map_load->setTransitions(new Transition(map_load, map_load, "loadmap"));
	map_load->setTransitions(new Transition(map_load, map_valid, "validatemap"));
	map_valid->setTransitions(new Transition(map_valid, players_added, "addplayer"));
	players_added->setTransitions(new Transition(players_added, players_added, "addplayer"));
	players_added->setTransitions(new Transition(players_added, game_start, "gamestart"));
    game_start->setTransitions(new Transition(game_start, issue_orders, "issueorder"));
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
void GameEngine::startupPhase()
{
	std::string input;
    Player* temp_player;
    int num_of_players;
	int index;

	while (!currentState->isEnd())
	{
        std::cout << "Currently at state " << (*currentState) << ". Enter the state you want to transition to: " << std::endl;
		std::cin >> input;
		if ((index = currentState->getCommandIndex(input)) == -1)
			std::cout << "No command: \"" << input << "\" usable from current state! Currently at state " << (*currentState) << std::endl;
		else
		{
			currentState = (currentState->getTransition(index))->getState();
			std::cout << "Transition to state: \"" << (*currentState) << "\"" << std::endl;

            if (currentState == states[1]) {
                std::cout << "Enter the map you want to load in the game: " << std::endl;
                std::cin >> input;
                map = new Map(MapLoader::loadMap( dir + input));
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
                std::cout << "Enter the number of players joining the game (2-6): " << std::endl;
                std::cin >> num_of_players;
                if (num_of_players + players.size() > MAX_NUM_PLAYERS) {
                    std::cout << "Max number of players reached, failed to add these players!" << std::endl;
                    continue;
                }
                for (int i {0}; i < num_of_players; i++) {
                    std::cout << "Enter the player's name: " << std::endl;
                    std::cin >> input;
                    temp_player = new Player(input);
                    players.push_back(temp_player);
                }
                std::cout << "Players added successfully" << std::endl;
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
                    initializeDeck();
                    for (int i {0}; i < players.size(); i++) {
                        players.at(i)->setArmies(50);
                        std::cout << "Player " << *(players.at(i)) << " currently has " << players.at(i)->getArmies() << " reserved troops in their inventory."<< std::endl;
                        std::cout << "Player " << *(players.at(i)) << " will now pick 2 cards from the deck!" << std::endl;
                        players.at(i)->getHand()->drawFromDeck(new_deck);
                        players.at(i)->getHand()->drawFromDeck(new_deck);
                    }
                }
            }
		}
	}
    std::cout << "Game over! Thank you for playing!" << std::endl;
}
void GameEngine::mainGameLoop() {
    std::cout << "Main Game Loop starting..." << std::endl;
    gameOver = false;
    map->checkContinentOwners();
    while (!gameOver) {
        reinforcementPhase(); //go to states[4]
        issueOrdersPhase(); //go to states[5]
        executeOrdersPhase(); //go to states[6]
    }
    bool playAgain = false;
    if (playAgain) {
        //go to states[1]
    }
    else {
        //exit() go to win state
    }
}



bool GameEngine::issueOrdersPhase() {
    std::cout << "Entering the issue orders phase. "<< std::endl;
    //Go through each player
    for (int current = 0; current < players.size(); current++) {
        Player *current_p = players.at(current); //get current player
        vector<Territory *> *toAttack = current_p->toAttack(); //get list of territories toAttack
        vector<Territory *> *toDefend = current_p->toDefend(); //get list of territories toDefend
        vector<Territory *> *toMove = current_p->getToMove(); //get list of territories to move troops from
        int armies = current_p->getArmies();
        int i;
        while (armies > 0) { //Deploy armies evenly across all the toDefend territories
            current_p->issueOrder(new Deploy(current_p, toDefend->at(i), 1)); //at toDefend[i]
            i++;
            if (i == toDefend->size()) {
                i = 0;
            }
            armies--;
        }
        current_p->setArmies(0); //reset player armies
        for (Territory *t : *toMove) { //for every territory NOT bordering an enemy territory with armies
            bool moved = false;
            int n = t->getNumberOfArmies();
            for (Territory *D : *toDefend) { //if that territory borders a toDefend territory, advance troops there
                if (order::isBeside(t, D)) {
                    current_p->issueOrder(new Advance(current_p, t, D, n)); //src : t, target : toDefend[i]
                    moved = true;
                    break;
                }
            }
            if (!moved) { //otherwise spread the troops out between a bordering territory
                current_p->issueOrder(new Advance(current_p, t, t->getEdges()[0], n/2));
            }
        }
        while (!toAttack->empty()) {
            Territory *player_t = toAttack->back(); //pop the player territory bordering an enemy's
            int n = player_t->getNumberOfArmies();
            toAttack->pop_back();
            Territory *enemy_t = toAttack->back(); //pop the enemy's territory
            toAttack->pop_back();
            current_p->issueOrder(new Advance(current_p, player_t, enemy_t, n)); //Attack it
        }
        //current player issues order from hand somehow...
        Hand *h = current_p->getHand();
        int next = current + 1;
        h->playRound(new_deck, current_p, players[next]);
    }
}
bool GameEngine::reinforcementPhase() {
    int n;
    //Go through every player
    for (Player *p : players) {
        //If player owns all the Territories, the game over.
        if (p->getTerritoryCount() == map->getNumOfTers()) {
            cout << *p->getName() << " has won the game!" << endl;
            gameOver = true;
            return false;
        }
        //Otherwise, calculate reinforcement pool and give it to the player.
        n = p->getTerritoryCount()/3;
        for (Continent *c : *p->getContinents()) {
            n += c->getBonus();
        }
        if (n < 3) {
            n = 3;
        }
        p->setArmies(n);
    }
    return true;
}
bool GameEngine::executeOrdersPhase() {
    int skipped;
    int current = 0;
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
            orders->popTop()->execute();
        }
        else {
            skipped++;
        }

        if (skipped == players.size()) {
            //If all the players have skipped, phase is over and return true
            return true;
        }
        current++;
        if (current == players.size()) {
            current = 0;
        }
    }
}
