#ifndef PLAYER_H
#define PLAYER_H

#include "../Part 1/Map.h"
#include "../Part 3/Orders.h"

#include <string>

class Player {
	private:
		OrdersList* orderList;
		std::vector<Territory*> territories;
		// Hand* hand;

	public:
		std::vector<Territory*> toDefend();
		std::vector<Territory*> toAttack();

		void issueOrder(std::string);
};

#endif