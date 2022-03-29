

#include "CommandProcessor.h" 
#include<iostream>
#include<fstream>

using namespace std;

 //__________________________________
 // CommandProcessor
 //__________________________________

//CONSTRUCTOR
CommandProcessor::CommandProcessor(GameEngine* ge){

}

CommandProcessor::CommandProcessor(GameEngine* ge){
    this->gameEng = ge; 
    lastCmd = Command(""); 
}

CommandProcessor::CommandProcessor(GameEngine* ge, const vector<Command> & lst){
    this->gameEng = ge; 
    commandList = lst;
    lastCmd = Command(""); 
}

//DESTRUCTOR
CommandProcessor::~CommandProcessor(){
    commandList.clear();
    this->gameEng = nullptr; 
}
    
bool CommandProcessor::validate(Command cmd, GameEngine ge){
    string state = *ge.currentState->name;
    string command = *cmd.command;
    if (command.compare("loadmap") == 0) {
        if (state.compare("start") == 0 || state.compare("maploaded") == 0)
            return true;
    }
    if (command.compare("validatemap") == 0) {
        if (state.compare("maploaded") == 0)
            return true;
    }
    if (command.compare("addplayer") == 0) {
        if (state.compare("mapvalidated") == 0 || state.compare("playersadded") == 0)
            return true;
    }
    if (command.compare("gamestart") == 0) {
        if (state.compare("playersadded") == 0)
            return true;
    }
    if (command.compare("replay") == 0) {
        if (state.compare("win") == 0)
            return true;
    }
    if (command.compare("quit") == 0) {
        if (state.compare("win") == 0)
            return true;
    }
    return false;
} 

void CommandProcessor::getCommand(){
    std::cout << "Enter -console if you want to enter commands on the console and -file <filename> for commands from a console.";
    string input; 
    std::cin >> input;
    if (input.compare("-console") == 0){
        std::cout << "Will read input from console.";
        readCommand(input);
    }
    else {
        input = input.substr(5, -1);
        std::cout << "Will read input from file named " << input;
        FileCommandProcessorAdapter fcpa = FileCommandProcessorAdapter(this);
        fcpa.readFileLine(input); 
    }
}
    
void CommandProcessor::readCommand(string cmd = ""){
    string usr_input; 
    std::cin >> usr_input; 
    this->lastCmd = Command(usr_input);
    saveCommand(); 
}
    
void CommandProcessor::saveCommand(){
    commandList.push_back(this->lastCmd);
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

void FileCommandProcessorAdapter::readCommand(string cmd = ""){
    commandProcessor->readCommand(cmd);
}

void FileCommandProcessorAdapter::readFileLine(string fileName = ""){
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

FileLineReader::readLinefromFile(string fileName = ""){
    fstream file;
    file.open(fileName,ios::out);
    
    if (file.is_open()){  
        string cmd;
        while(getline(file, cmd)){ 
            if (validate(cmd)){
                this->lastCmd = cmd; 
                saveCommand();
            }
            else {
                this->lastCmd = Command("Invalid Command.");
                saveCommand();
            }
        }
        file.close(); 
    }
}

