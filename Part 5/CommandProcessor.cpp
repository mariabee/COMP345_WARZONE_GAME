

#include "CommandProcessor.h"
#include "GameEngine.h"
#include<iostream>
#include<fstream>
#include <utility>

using namespace std;

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
    delete effect;
    effect = e;
    notify();
}

std::string Command::stringToLog() {
    return "COMMAND::\"" + *effect + "\"";
}

// Destructor for Command
Command::~Command() {
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


 //__________________________________
 // CommandProcessor
 //__________________________________

//CONSTRUCTOR
CommandProcessor::CommandProcessor(){
    lastCmd = nullptr;
    commandList = new vector<Command *>();
    inputType = nullptr;
}

CommandProcessor::CommandProcessor(CommandProcessor *c){
    delete commandList;
    delete lastCmd;
    delete inputType;
    commandList = c->commandList;
    lastCmd = c->lastCmd;
    inputType = c->inputType;
}

//DESTRUCTOR
CommandProcessor::~CommandProcessor(){
    delete lastCmd;
    for (Command *c : *commandList) {
        delete c;
    }
    commandList->clear();
}

bool CommandProcessor::checkTournament(const Command& cmd, GameEngine* ge) {
    string* state = ge->currentState->name;
    string command = *cmd.command;

    if (*state == "start") {
        if (TournamentModeHandler::fromString(command))
            return true;
    }
    return false;

}
    
bool CommandProcessor::validate(const Command& cmd, GameEngine* ge){
    string* state = ge->currentState->name;
    string command = *cmd.command;
    if (command == "loadmap") {
        if (*state == "start" || *state == "maploaded")
            return true;
    }
    if (command == "validatemap") {
        if (*state == "map_loaded")
            return true;
    }
    if (command == "addplayer") {
        if (*state == "map_validated" || *state == "players_added")
            return true;
    }
    if (command == "gamestart") {
        if (*state == "players_added")
            return true;
    }
    if (command == "replay") {
        if (*state == "win")
            return true;
    }
    if (command == "quit") {
        if (*state == "win")
            return true;
    }
    return false;
} 

void CommandProcessor::getCommand(){
    while (true) {
        if (!inputType) {
            std::cout
                    << "Enter -console if you want to enter commands on the console and -file to read commands from a file.\n";
            string input;
            std::cin >> input;
            inputType = new string(input);
        }
        if (*inputType == "-console") {
            readCommand();
            return;
        } else if (*inputType == "-file") {
            auto *adapter = new FileCommandProcessorAdapter();
            adapter->getCommand();
            setCommandList(adapter->getCommandList());
            return;
        } else {
            cout << "Invalid choice." << endl;
            inputType = nullptr;
        }
    }
}

void CommandProcessor::readCommand(){
    std::cout << "Reading input from console...\n";
    string input;
    cin >> input;
    if (input == "0") {
        return;
    }
    this->lastCmd = new Command(input);
    saveCommand();
    if (input == "loadmap") {
        cout << "Command entered to load map. Please enter the filename :" << endl;
        cin >> input;
        this->lastCmd = new Command(input);
        saveCommand();
    }
    if (input == "addplayer") {
        cout << "Command entered to add player. Please enter the number of players, followed by their names: " << endl;
        int n;
        cin >> n;
        this->lastCmd = new Command(to_string(n));
        saveCommand();
        for (int i = 0; i < n; i++) {
            cin >> input;
            this->lastCmd = new Command(input);
            saveCommand();
        }
        return;
    }
    if (*lastCmd->command == "gamestart") {
        cout << "Game has finished. Enter play to play again, or end to quit.";
    }
}
    
void CommandProcessor::saveCommand(){
    commandList->push_back(lastCmd);
}

void CommandProcessor::setLastCommand(Command* c) {
    lastCmd = c;
}

void CommandProcessor::setCommandList(vector<Command *> *c) {
    resetCommandList();
    for (Command *c_ : *c) {
        commandList->push_back(c_);
    }
}

vector<Command *> *CommandProcessor::getCommandList() {
    return commandList;
}

void CommandProcessor::resetCommandList() {
    for (Command *c : *commandList) {
        delete c;
    }
    commandList->clear();
}


//__________________________________
 // FileCommandProcessorAdapter
 //__________________________________

//CONSTRUCTOR
FileCommandProcessorAdapter::FileCommandProcessorAdapter(){
    this->fileLineReader = new FileLineReader();
}
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileCommandProcessorAdapter *f){
    delete fileLineReader;
    this->fileLineReader = f->getFileLineReader();
}
//DESTRUCTOR
FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
    delete fileLineReader;
    this->fileLineReader = nullptr; 
}

void FileCommandProcessorAdapter::getCommand(){
    string input;
    std::cout << "Please enter your file path: \n";
    cin >> input;
    vector<Command *> *commands = fileLineReader->getFileCommands(input);
    setCommandList(commands);
}

FileLineReader *FileCommandProcessorAdapter::getFileLineReader() {
    return fileLineReader;
}

//__________________________________
 // FileLineReader
 //__________________________________

vector<Command *> * FileLineReader::getFileCommands(const string& path){
    string dir {"../Debug/"};
    ifstream input(dir + path);
    if (!input) {
        cout << "Invalid file path." << endl;
        return nullptr;
    }
    auto *commands = new vector<Command *>();
    cout << "Reading file..." << endl;

    string cmd;
    while(getline(input, cmd)){
        auto *command = new Command(cmd);
        commands->push_back(command);
    }
    input.close();

    return commands;
}

FileLineReader::FileLineReader() = default;

