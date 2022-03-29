
class Command;

class CommandProcessor {
public:
	Command* getCommand();

private:
	Command** commands;
	void readCommand();
	void saveCommand();
	void validate();
};