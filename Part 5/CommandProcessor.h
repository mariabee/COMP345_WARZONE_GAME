#ifndef COMMANDPROCESSIOR_H
#define COMMANDPROCESSOR_H
#include "../Part5/GameEngine.h" 
#include <iostream>
#include <vector>

class CommandProcessor{
    
private: 
    vector<Command> commandList; 
    Command lastCmd; 
    virtual void readCommand(string cmd); 
    void saveCommand(); 

    
public: 
    //CONSTRUCTOR
    CommandProcessor(); 
    CommandProcessor(const std::vector<Command> & lst); 
    
    //DESTRUCTOR
    ~CommandProcessor();
    
    bool validate(Command cmd, GameEngine ge); 
    void getCommand(); 
    
};

class FileLineReader{
private:
    string textfile; 
    virtual void FileLineReader(string fileName);
    
public: 
    //CONSTRUCTOR
    FileLineReader(); 
    
    //DESTRUCTOR
    ~FileLineReader();
};

class FileCommandProcessorAdapter: public CommandProcessor, public FileLineReader{
    
private:
    FileLineReader *fileLineReader;
    CommandProcessor *commandProcessor;
    virtual void readCommand(string fileName); 
    virtual void FileLineReader(string fileName);
    
public: 
    //CONSTRUCTOR
    FileCommandProcessorAdapter(CommandProcessor *cp); 
    FileCommandProcessorAdapter(FileLineReader *flr);

    //DESTRUCTOR
    ~FileCommandProcessorAdapter();
};



#endif