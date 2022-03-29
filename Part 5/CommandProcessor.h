
#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include "GameEngine.h" 
#include <iostream>
#include <vector>



class CommandProcessor{
    
private: 
    GameEngine* gameEng; 
    vector<Command *> commandList;
    Command* lastCmd;


    
public: 
    //CONSTRUCTOR
    CommandProcessor();
    CommandProcessor(GameEngine* ge); 
    CommandProcessor(GameEngine* ge, const std::vector<Command* > & lst);
    void saveCommand();

    //DESTRUCTOR
    virtual ~CommandProcessor();
    
    bool validate(Command cmd, GameEngine* ge);
    void getCommand(); 
    virtual void readCommand(string cmd);
    void setLastCommand(Command*);
    
};

class FileLineReader: public CommandProcessor{
private:

    string textfile;
    
public: 
    //CONSTRUCTOR
    FileLineReader();
    FileLineReader(string);
    //DESTRUCTOR
    virtual ~FileLineReader();
    
    void readLineFromFile(string fileName,GameEngine* ge);
};

class FileCommandProcessorAdapter: public FileLineReader{
    
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
    virtual void readFileLine(string fileName);
};



#endif