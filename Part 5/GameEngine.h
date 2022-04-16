#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "LoggingObserver.h"

#include <string>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "CommandProcessor.h"

#define START_STATE "start"
#define END_STATE "end"

class State;

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
	bool matches(const std::string& s);
};

class State
{
public:
	State& operator=(const State &s);
	State(const State &s);
	explicit State(std::string n);
	friend std::ostream& operator<< (std::ostream &out, const State &s);
	~State();
	std::string& toString() const;
	bool isEnd() const;
	int getCommandIndex(const std::string& s);
	Transition *getTransition(int i);
	void setTransitions(Transition *t);

	std::string* name;

private:
	int index = 0;
	Transition **transitions = new Transition *[2];
};

class GameEngine: public Subject, public ILoggable
{
private:
    const std::string dir {"../Debug/MapFiles/"};
    const int MAX_NUM_PLAYERS {6};
    const int MIN_NUM_PLAYERS {2};
    vector<Player *> players;
    Map *map;
	State **states;
    PlayerStrategy **strategies;
    Deck* new_deck;
	int stateCount;
    bool gameOver;
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();
public:
	State *currentState;
	std::string stringToLog() override;
	GameEngine& operator=(const GameEngine &ge);
	GameEngine(const GameEngine &ge);
	GameEngine();
	friend std::ostream& operator<< (std::ostream &out, const GameEngine &ge);
	~GameEngine() override;
	void build();
	void startupPhase(Command *c, vector<Command *> *commands);
    void distributeTerritories();
    void mainGameLoop(CommandProcessor *cp);
    void randomizePlayOrder();
    void initializeDeck();
    void initializeStrategies();
    void setState(const std::string& s);
    void initial_start(CommandProcessor *cp);
    void testPhase();

    void play();

    void checkWinner();
};

#endif