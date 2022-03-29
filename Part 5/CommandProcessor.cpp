

#include "CommandProcessor.h" 
#include<iostream>
#include<fstream>

using namespace std;

 //__________________________________
 // CommandProcessor
 //__________________________________

//CONSTRUCTOR
CommandProcessor::CommandProcessor(){

}

CommandProcessor::CommandProcessor(GameEngine* ge){
    this->gameEng = ge; 
    lastCmd = new Command("");
}

CommandProcessor::CommandProcessor(GameEngine* ge, const vector<Command *> & lst){
    this->gameEng = ge; 
    commandList = lst;
    lastCmd = new Command("");
}

//DESTRUCTOR
CommandProcessor::~CommandProcessor(){
    commandList.clear();
    this->gameEng = nullptr; 
}
    
bool CommandProcessor::validate(Command cmd, GameEngine* ge){
    string* state = ge->currentState->name;
    string command = *cmd.command;
    if (command.compare("loadmap") == 0) {
        if (state->compare("start") == 0 || state->compare("maploaded") == 0)
            return true;
    }
    if (command.compare("validatemap") == 0) {
        if (state->compare("maploaded") == 0)
            return true;
    }
    if (command.compare("addplayer") == 0) {
        if (state->compare("mapvalidated") == 0 || state->compare("playersadded") == 0)
            return true;
    }
    if (command.compare("gamestart") == 0) {
        if (state->compare("playersadded") == 0)
            return true;
    }
    if (command.compare("replay") == 0) {
        if (state->compare("win") == 0)
            return true;
    }
    if (command.compare("quit") == 0) {
        if (state->compare("win") == 0)
            return true;
    }
    return false;
} 

void CommandProcessor::getCommand(){
    std::cout << "Enter -console if you want to enter commands on the console and -file for commands from a file.\n";
    string input; 
    std::cin >> input;
    if (input.compare("-console") == 0){
        std::cout << "Will read input from console.\n";
    }
    else {
        std::cout << "Please enter your file name: \n";
        cin >> input;
        FileCommandProcessorAdapter fcpa = FileCommandProcessorAdapter(new FileLineReader(input));
        fcpa.readFileLine(input); 
    }
}
    
void CommandProcessor::readCommand(string cmd){
    this->lastCmd = new Command(cmd);
    saveCommand(); 
}
    
void CommandProcessor::saveCommand(){
    commandList.push_back(this->lastCmd);
}

void CommandProcessor::setLastCommand(Command* c) {
    this->lastCmd = c;
}
 
 //__________________________________
 // FileCommandProcessorAdapter
 //__________________________________

//CONSTRUCTOR
FileCommandProcessorAdapter::FileCommandProcessorAdapter(CommandProcessor *cp){
    this->commandProcessor = cp;
    this->fileLineReader = NULL;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader *flr){
    this->commandProcessor = NULL;
    this->fileLineReader = flr;
} 

//DESTRUCTOR
FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
    delete commandProcessor;
    delete fileLineReader;
    this->commandProcessor = nullptr;
    this->fileLineReader = nullptr; 
}

void FileCommandProcessorAdapter::readCommand(string cmd){
    commandProcessor->readCommand(cmd);
}

void FileCommandProcessorAdapter::readFileLine(string fileName){
    readFileLine(fileName);
}
    
 //__________________________________
 // FileLineReader
 //__________________________________
 

//CONSTRUCTOR
FileLineReader::FileLineReader(){
    this->textfile = "";
}
    
//DESTRUCTOR
FileLineReader::~FileLineReader(){
    this->textfile = nullptr;
}

void FileLineReader::readLineFromFile(string fileName,GameEngine* ge){
    fstream file;
    file.open(fileName,ios::out);
    
    if (file.is_open()){  
        string cmd;
        while(getline(file, cmd)){ 
            if (validate(Command(cmd),ge)){
                this->setLastCommand(new Command(cmd));
                this->saveCommand();
            }
            else {
                this->setLastCommand(new Command("Invalid Command."));
                this->saveCommand();
            }
        }
        file.close(); 
    }
}

FileLineReader::FileLineReader(string name) {
    this->textfile = name;
}

