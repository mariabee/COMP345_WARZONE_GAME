
#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include <iostream>
#include <vector>
#include "LoggingObserver.h"
using std::vector;
using std::string;

class GameEngine;
// Class that provides functionality to match a Command.
class Command: public Subject, public ILoggable
{
public:
    Command& operator=(const Command &c);
    Command(const Command &c);
    explicit Command(std::string c);
    friend std::ostream& operator<<(std::ostream &out, const Command &c);
    bool matches(const std::string& s) const;
    std::string stringToLog() override;
    void saveEffect(std::string* e);
    ~Command() override;


    std::string* command;

private:
    std::string* effect;
};

class CommandProcessor{

private:
    vector<Command *> *commandList;
    Command* lastCmd;
    string *inputType;
protected:
    void readCommand();
    void saveCommand();
public:
    //CONSTRUCTOR
    CommandProcessor();
    explicit CommandProcessor(CommandProcessor *c);
    //DESTRUCTOR
    virtual ~CommandProcessor();
    static bool validate(const Command& cmd, GameEngine* ge);
    virtual void getCommand();
    void setLastCommand(Command*);
    void setCommandList(vector<Command *> *c);
    void resetCommandList();
    vector<Command *> * getCommandList();

};

class FileLineReader {
private:
public:
    FileLineReader();
    vector<Command *> * getFileCommands(const string& path);
};


class FileCommandProcessorAdapter: public CommandProcessor {

private:
    FileLineReader* fileLineReader;
public:
    //CONSTRUCTOR
    FileCommandProcessorAdapter();
    explicit FileCommandProcessorAdapter(FileCommandProcessorAdapter *f);
    //DESTRUCTOR
    virtual ~FileCommandProcessorAdapter();
    void getCommand() override;
    FileLineReader * getFileLineReader();
};
#endif