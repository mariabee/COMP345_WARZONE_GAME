#include "Player.h"
#include <map>

class Territory;
std::vector<Territory *> Player::toDefend()
{
	std::vector<Territory *> out;

	for (int i = 0; i < territories.size(); i++)
		out.push_back(territories[i]);

	return out;
}

std::vector<Territory *> Player::toAttack()
{
	std::vector<Territory *> out;

	// std::string orderTypes = {"deploy"};

	for (int i = 0; i < territories.size(); i++)
		out.push_back(territories[i]);

	return out;
}

void Player::issueOrder(std::string type)
{
	map<std::string, int> test;
	test["deploy"] = 0;
	test["advance"] = 1;
	test["bomb"] = 2;
	test["blockade"] = 3;
	test["airlift"] = 4;
	order *o;

	switch (test.at(type))
	{
	case 0:
		o = new Deploy();
		break;
	case 1:
		o = new Advance();
		break;
	case 2:
		o = new Bomb();
		break;
	case 3:
		o = new Blockade();
		break;
	case 4:
		o = new Airlift();
		break;
	default:
		std::cout << "Error::Player - Unknown Type: " << type;
		return;
	}

	std::cout << "Player - Successfully issued order: " << type;
	orderList->add(o);
}