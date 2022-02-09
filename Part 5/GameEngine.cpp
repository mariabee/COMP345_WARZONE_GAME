#include "GameEngine.h"

void Command::operator=(Command &c)
{
	command = c.command;
}

Command::Command(Command &c)
{
	command = c.command;
}

Command::~Command()
{
	std::cout << "Deleting command: \"" << command << "\"" << std::endl;
}

Command::Command(std::string c)
{
	command = c;
}

bool Command::matches(std::string s)
{
	return command == s;
}

void Transition::operator=(Transition &t)
{
	from = t.from;
	to = t.to;
	on = t.on;
}

Transition::Transition(Transition &t)
{
	from = t.from;
	to = t.to;
	on = t.on;
}

Transition::Transition(State *f, State *t, std::string o)
{
	from = f;
	to = t;
	on = new Command(o);
}

Transition::~Transition()
{
	std::cout << "Deleting transition" << std::endl;
	delete on;
}

State *Transition::getState()
{
	return to;
}

bool Transition::matches(std::string s)
{
	return on->matches(s);
}

void State::operator=(State &s)
{
	acceptedCommands = s.acceptedCommands;
	index = s.index;
	name = s.name;
	transitions = s.transitions;
}

State::State(State &s)
{
	acceptedCommands = s.acceptedCommands;
	index = s.index;
	name = s.name;
	transitions = s.transitions;
}

State::State(std::string n)
{
	name = n;
}

State::State(std::string n, Transition **t)
{
	name = n;
	transitions = t;
}

State::~State()
{
	std::cout << "Deleting state: \"" << name << "\"" << std::endl;
	for (int i = 0; i < index; i++)
		delete transitions[i];
	delete transitions;
	delete acceptedCommands;
}

std::string State::toString()
{
	return name;
}

int State::getCommandIndex(std::string s)
{
	for (int i = 0; i < index; i++)
	{
		if (transitions[i]->matches(s))
			return i;
	}
	return -1;
}

Transition *State::getTransition(int i)
{
	return transitions[i];
}

void State::setTransitions(Transition *t)
{
	transitions[index++] = t;
}

void GameEngine::operator=(GameEngine &ge)
{
	currentState = ge.currentState;
	start();
}

GameEngine::GameEngine(GameEngine &ge)
{
	currentState = ge.currentState;
	start();
}

GameEngine::GameEngine()
{
	build();
	start();
}

GameEngine::~GameEngine()
{
	for (int i = 0; i < stateCount; i++)
		delete states[i];
	delete states;
}

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