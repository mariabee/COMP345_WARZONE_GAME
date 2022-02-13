#include "GameEngine.h"

// Assignment operator overload for Command
void Command::operator=(Command &c)
{
	command = c.command;
}

// Copy constructor for Command
Command::Command(Command &c)
{
	command = c.command;
}

// Destructor for Command
Command::~Command()
{
	std::cout << "Deleting command: \"" << command << "\"" << std::endl;
}

// Constructor for Command that takes a string
Command::Command(std::string c)
{
	command = c;
}

// Function that returns a boolean corresponding to whether a given string matches the command
bool Command::matches(std::string s)
{
	return command == s;
}

// Assignment operator overload for Transition
void Transition::operator=(Transition &t)
{
	from = t.from;
	to = t.to;
	on = t.on;
}

// Copy constructor for Transition
Transition::Transition(Transition &t)
{
	from = t.from;
	to = t.to;
	on = t.on;
}

// Constructor for Transtion that takes two states one start and one destination, 
// and a string corresponding to the command that transitions between them
Transition::Transition(State *f, State *t, std::string o)
{
	from = f;
	to = t;
	on = new Command(o);
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
void State::operator=(State &s)
{
	acceptedCommands = s.acceptedCommands;
	index = s.index;
	name = s.name;
	transitions = s.transitions;
}

// Copy constructor for State
State::State(State &s)
{
	acceptedCommands = s.acceptedCommands;
	index = s.index;
	name = s.name;
	transitions = s.transitions;
}

// Constructor for State that takes in a name
State::State(std::string n)
{
	name = n;
}

// Constructor for State 
State::State(std::string n, Transition **t)
{
	name = n;
	transitions = t;
}

// Destructor for State
State::~State()
{
	std::cout << "Deleting state: \"" << name << "\"" << std::endl;
	for (int i = 0; i < index; i++)
		delete transitions[i];
	delete transitions;
	delete acceptedCommands;
}

// Returns string corresponding with state 
std::string State::toString()
{
	return name;
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
void GameEngine::operator=(GameEngine &ge)
{
	currentState = ge.currentState;
	start();
}

// Copy constructor for GameEngine
GameEngine::GameEngine(GameEngine &ge)
{
	currentState = ge.currentState;
	start();
}

// Default constructor for GameEngine
GameEngine::GameEngine()
{
	build();
	start();
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

	auto start = new State("start");
	currentState = start;
	auto map_load = new State("map_loaded");
	auto map_valid = new State("map_validated");
	auto players_added = new State("players_added");
	auto assign_reinforcement = new State("assign_reinforcement");
	auto issue_orders = new State("issue_orders");
	auto execute_orders = new State("execute_orders");
	auto win = new State("win");
	states = new State *[8]
	{ start, map_load, map_valid, players_added, assign_reinforcement, issue_orders, execute_orders, win };
	stateCount = 8;

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
}

// Function that starts the game engine, which waits for player input.
void GameEngine::start()
{
	std::string input;
	int index;
	while (true)
	{
		std::cin >> input;
		if ((index = currentState->getCommandIndex(input)) == -1)
			std::cout << "No command: \"" << input << "\" usable from current state!" << std::endl;
		else
		{
			currentState = (currentState->getTransition(index))->getState();
			std::cout << "Transition to state: \"" << currentState->toString() << "\"" << std::endl;
		}
	}
}