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
	std::cout << "Deleting command: \"" << *this << "\"" << std::endl;
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
	std::cout << "Deleting transition" << std::endl;
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
	std::cout << "Deleting state: \"" << *this << "\"" << std::endl;
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

// Function that builds the transition graph corresponding to the game engine, game state and commands.
void GameEngine::build()
{

	auto start = new State(START_STATE);
	currentState = start;
	auto map_load = new State("map_loaded");
	auto map_valid = new State("map_validated");
	auto players_added = new State("players_added");
	auto assign_reinforcement = new State("assign_reinforcement");
	auto issue_orders = new State("issue_orders");
	auto execute_orders = new State("execute_orders");
	auto win = new State("win");
	auto end = new State(END_STATE);
	states = new State *[9]
	{ start, map_load, map_valid, players_added, assign_reinforcement, issue_orders, execute_orders, win, end };
	stateCount = 9;

	start->setTransitions(new Transition(start, map_load, "loadmap"));
	map_load->setTransitions(new Transition(map_load, map_load, "loadmap"));
	map_load->setTransitions(new Transition(map_load, map_valid, "validatemap"));
	map_valid->setTransitions(new Transition(map_valid, players_added, "addplayer"));
	players_added->setTransitions(new Transition(players_added, players_added, "addplayer"));
	players_added->setTransitions(new Transition(players_added, assign_reinforcement, "assigncountries"));
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
void GameEngine::start()
{
	std::string input;
	int index;
	while (!currentState->isEnd())
	{
		std::cin >> input;
		if ((index = currentState->getCommandIndex(input)) == -1)
			std::cout << "No command: \"" << input << "\" usable from current state!" << std::endl;
		else
		{
			currentState = (currentState->getTransition(index))->getState();
			std::cout << "Transition to state: \"" << (*currentState) << "\"" << std::endl;
		}
	}
}
void GameEngine::mainGameLoop() {
    gameOver = false;
    map->checkContinentOwners();
    while (!gameOver) {
        reinforcementPhase();
        int firstUp = 0;
        issueOrdersPhase(firstUp);
        executeOrdersPhase(firstUp);
    }
    bool playAgain = false;
    if (playAgain) {
        start();
    }
    else {
        //exit() ?
    }
}



bool GameEngine::issueOrdersPhase(int firstUp) {
    int current = firstUp;
    while (true) {
        Player *current_p = players.at(current);
        current_p->issueOrder("TBA");
        int num = 5;
        Territory ** toAttack = current_p->toAttack(num);
        Territory ** toDefend = current_p->toDefend(num);
        int i;
        int armies = current_p->getArmies();
        while (armies > 0) {
            current_p->issueOrder("Deploy");
            //at toDefend[i]
            i++;
            armies--;
        }
        current_p->setArmies(0);
        for (Territory *t : *current_p->getToMove()) {
            bool moved;
            for (int i = 0; i < num; i++) { //get Num of to Attack
                if (order::isBeside(t, toAttack[i])) {
                    current_p->issueOrder("Advance"); //src : t, target : toAttack[i]
                }
            }
            for (int i = 0; i < num; i++) { // get num of toDefend
                if (order::isBeside(t, toAttack[i])) {
                    current_p->issueOrder("Advance"); // src : t, target : toDefend[i] //
                }
            }
        }
        //current player issue order from hand
        current++;
        if (current == players.size()) {
            current = 0;
        }
        if (current == firstUp) {
            return true;
        }
    }
}
bool GameEngine::reinforcementPhase() {
    int n;
    for (Player *p : players) {
        if (p->getTerritoryCount() == map->getNumOfTers()) {
            gameOver = true;
            return false;
        }
        n = p->getTerritoryCount()/3;
        for (Continent *c : *p->getContinents()) {
            n += c->getBonus();
        }
        p->setArmies(n);
    }
    return true;
}
bool GameEngine::executeOrdersPhase(int firstUp) {
    int skipped;
    int current = firstUp;
    while (true) {
        if (current == firstUp) {
            skipped = 0;
        }
        Player *current_p = players.at(current);
        OrdersList *orders = current_p->getOrdersList();
        if (!orders->getList()->empty()) {
            orders->popTop()->execute();
        }
        else {
            skipped++;
        }

        if (skipped == players.size()) {
            return true;
        }
        current++;
        if (current == players.size()) {
            current = 0;
        }
    }
}
