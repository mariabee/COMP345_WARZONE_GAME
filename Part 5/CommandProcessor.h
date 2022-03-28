
#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include "GameEngine.h" 
#include <iostream>
#include <vector>

class CommandProcessor{
    
private: 
    GameEngine* gameEng; 
    vector<Command> commandList; 
    Command lastCmd; 
    void saveCommand(); 

    
public: 
    //CONSTRUCTOR
    CommandProcessor();
    CommandProcessor(GameEngine* ge); 
    CommandProcessor(GameEngine* ge, const std::vector<Command> & lst); 
    
    //DESTRUCTOR
    virtual ~CommandProcessor();
    
    bool validate(Command cmd, GameEngine ge); 
    void getCommand(); 
    virtual void readCommand(string cmd); 
    
};

class FileLineReader{
private:
    string textfile; 
    
public: 
    //CONSTRUCTOR
    FileLineReader(); 
    
    //DESTRUCTOR
    virtual ~FileLineReader();
    
    void readLinefromFile(string fileName);
};

class FileCommandProcessorAdapter: public CommandProcessor, public FileLineReader{
    
private:
    FileLineReader* fileLineReader;
    CommandProcessor* commandProcessor;

public: 
    //CONSTRUCTOR
    FileCommandProcessorAdapter(CommandProcessor *cp); 
    FileCommandProcessorAdapter(FileLineReader *flr);

    //DESTRUCTOR
    virtual ~FileCommandProcessorAdapter();
    
    virtual void readCommand(string fileName); 
    virtual void fileLineReader(string fileName);
};



#endif