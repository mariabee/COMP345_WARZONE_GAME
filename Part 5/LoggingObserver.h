#pragma once
#include <string>
#include <iostream>

class ILoggable {
public:
	virtual std::string stringToLog() = 0;
};

class Observer {
public:
	Observer();
	Observer(const Observer& subject);
	Observer* operator=(const Observer& subject);
	friend std::ostream& operator<<(std::ostream& out, const Observer& subject);
	virtual ~Observer();
	virtual void update(ILoggable* loggable) = 0;
};

class Subject {
	public:
	Subject();
	Subject(int s);
	Subject(const Subject& subject);
	Subject* operator=(const Subject& subject);
	friend std::ostream& operator<<(std::ostream& out, const Subject& subject);
	virtual ~Subject();

	virtual void notify();
};

// Singleton
class LogObserver: public Observer {

	public:
	LogObserver(const LogObserver& subject);
	LogObserver* operator=(const LogObserver& subject);
	friend std::ostream& operator<<(std::ostream& out, const LogObserver& subject);
	virtual ~LogObserver();
	void update(ILoggable* loggable);
	static LogObserver& getInstance();
	
	private: 
	LogObserver();

	void writeToLogFile(std::string str);
};