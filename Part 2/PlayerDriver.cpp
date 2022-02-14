#include <iostream>
#include "Player.h"

int main(){
    auto *t1 = new Territory(0, "test1", 0);
    auto *t2 = new Territory(1, "test2", 0);
    auto *t3 = new Territory(2, "test3", 0);
	Player p("player1");
	p.setTerritories(new Territory*[3] {t1, t2, t3}, 3);

	int ct = 0;

	Territory** attacking = p.toAttack(ct);

	for (int i = 0; i < ct; i++)
		std::cout << p << ": Preparing to attack: " << *attacking[i] << std::endl;


	Territory** defending = p.toDefend(ct);
	for (int i = 0; i < ct; i++)
		std::cout << p << ": Preparing to defend: " << *defending[i] << std::endl;

	p.issueOrder("deploy");
}