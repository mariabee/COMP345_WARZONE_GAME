#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <string>
#include <iostream>

class State;

// Class that provides functionality to match a Command.
class Command
{
public:
	void operator=(Command &c);
	Command(Command &c);
	Command(std::string c);
	friend std::ostream& operator<<(std::ostream &out, const Command &c);
	bool matches(std::string s);
	~Command();

private:
	std::string command;
};

class Transition
{
private:
	State *from;
	State *to;
	Command *on;

public:
	void operator=(Transition &t);
	Transition(Transition &t);
	friend std::ostream& operator<<(std::ostream &out, const Transition &t);
	~Transition();
	Transition(State *f, State *t, std::string o);
	State *getState();
	bool matches(std::string s);
};

class State
{
public:
	void operator=(State &s);
	State(State &s);
	State(std::string n);
	friend std::ostream& operator<< (std::ostream &out, const State &s);
	~State();
	int getCommandIndex(std::string s);
	Transition *getTransition(int i);
	void setTransitions(Transition *t);

private:
	std::string name;
	int index = 0;
	Transition **transitions = new Transition *[2];
	Command *acceptedCommands;
};

class GameEngine
{
private:
	State *currentState;
	State **states;
	int stateCount;

public:
	void operator=(GameEngine &ge);
	GameEngine(GameEngine &ge);
	GameEngine();
	friend std::ostream& operator<< (std::ostream &out, const GameEngine &ge);
	~GameEngine();
	void build();
	void start();
};

#endif