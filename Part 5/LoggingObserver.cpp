#include "LoggingObserver.h"
#include <fstream>

Observer::Observer() {

}

Observer::Observer(const Observer& subject) {

}

std::ostream& operator<<(std::ostream& out, const Observer& subject) {
	out << "Observer";
	return out;

}

Observer::~Observer() {

}

Observer* Observer::operator=(const Observer& subject) {

	 return this;
}


Subject::Subject() {
}

Subject::Subject(const Subject& subject) {
}

Subject* Subject::operator=(const Subject& subject) {
	return this;
}

std::ostream& operator<<(std::ostream& out, const Subject& subject) {
	out << "Subject";
	return out;
}

Subject::~Subject() {
}

void Subject::notify()
{
	LogObserver::getInstance().update(dynamic_cast<ILoggable*>(this));
}

LogObserver::LogObserver() {
	std::fstream file("gamelog.txt", std::fstream::out);
	file << "";
	file.close();
}

LogObserver& LogObserver::getInstance() {
	static LogObserver instance;
	return instance;
}

LogObserver::LogObserver(const LogObserver& subject) {

}

std::ostream& operator<<(std::ostream& out, const LogObserver& subject) {
	out << "LogObserver";
	return out;
}

LogObserver::~LogObserver() {

}

LogObserver* LogObserver::operator=(const LogObserver& subject) {
	return this;
}

void LogObserver::update(ILoggable *loggable)
{
	writeToLogFile(loggable->stringToLog());
}

void LogObserver::writeToLogFile(std::string str)
{
	std::fstream file("gamelog.txt", std::fstream::app);
	file << str << "\n";
	file.close();
}