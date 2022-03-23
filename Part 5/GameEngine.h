#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <string>
#include <iostream>
#include "Player.h"
#include "Map.h"

#define START_STATE "start"
#define END_STATE "end"

class State;

// Class that provides functionality to match a Command.
class Command
{
public:
	Command& operator=(const Command &c);
	Command(const Command &c);
	Command(std::string c);
	friend std::ostream& operator<<(std::ostream &out, const Command &c);
	bool matches(std::string s);
	~Command();

private:
	std::string* command;
};

class Transition
{
private:
	State *from;
	State *to;
	Command *on;

public:
	Transition& operator=(const Transition &t);
	Transition(const Transition &t);
	friend std::ostream& operator<<(std::ostream &out, const Transition &t);
	~Transition();
	Transition(State *f, State *t, std::string o);
	State *getState();
	bool matches(std::string s);
};

class State
{
public:
	State& operator=(const State &s);
	State(const State &s);
	State(std::string n);
	friend std::ostream& operator<< (std::ostream &out, const State &s);
	~State();
	bool isEnd();
	int getCommandIndex(std::string s);
	Transition *getTransition(int i);
	void setTransitions(Transition *t);

private:
	std::string* name;
	int index = 0;
	Transition **transitions = new Transition *[2];
	Command *acceptedCommands;
};

class GameEngine
{
private:
    vector <Player*> players;
    Map *map;
	State *currentState;
	State **states;
	int stateCount;
    bool gameOver;
    bool reinforcementPhase();
    bool issueOrdersPhase(int first_up);
    bool executeOrdersPhase(int first_up);
public:
	GameEngine& operator=(const GameEngine &ge);
	GameEngine(const GameEngine &ge);
	GameEngine();
	friend std::ostream& operator<< (std::ostream &out, const GameEngine &ge);
	~GameEngine();
	void build();
	void start();
    void mainGameLoop();
};

#endif