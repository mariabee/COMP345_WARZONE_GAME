#include "PlayerStrategy.h"
#include "Player.h"
#include "Cards.h"

Deck *PlayerStrategy::deck = nullptr;
vector<Player *> *PlayerStrategy::players = nullptr;
void PlayerStrategy::addDeck(Deck *d) {
    deck = d;
}
void PlayerStrategy::addPlayers(vector<Player *> *p) {
    players = p;
}

HumanPlayerStrategy::HumanPlayerStrategy() = default;

bool HumanPlayerStrategy::issueOrder(Player *player, order *o) {
        auto *negotiate  = dynamic_cast<Negotiate *>(o);
        if (negotiate) {
            Player *p = generateNegotiate();
            if (!p) return false;
            negotiate->setPlayer2(p);
            player->getOrdersList()->add(negotiate);
        }
        else {
            player->getOrdersList()->add(o);
        }
        return true;
}
void HumanPlayerStrategy::issueOrder(Player *p) {
    bool issueAgain;
    Player *player = p;
    int armies = player->getArmies();
    bool cardPlayed = false;
    do {
        cout << "Please select which order to issue : " << endl;
        int n;
        if (armies > 0) { cout << "1. Deploy troops " << endl;
            cout << "2. Advance troops " << endl;
            if (!cardPlayed) { cout << "3. Play a card " << endl; }
            cin >> n;
        }
        else {
            cout << "1. Advance troops " << endl;
            if (!cardPlayed) { cout << "2. Play a card " << endl; }
            cin >> n;
            n++;
        }

        vector<Territory *> *territories = player->getTerritories();
        vector<Territory *> *deployTo;
        switch(n) {
            case 1:
                Deploy *d;
                deployTo = toDefend(player, new Deploy());
                if (deployTo) {
                    cout << "You have " << armies << " troops available. How many troops would you like to deploy ? " << endl;
                    int num_deploy;
                    cin >> num_deploy;
                    if (num_deploy <= armies && armies > 0) {
                        d = new Deploy(player, deployTo->back(), num_deploy);
                        player->getOrdersList()->add(d);
                        cout << "Order to deploy " << num_deploy << " troops " << " to "
                            << *deployTo->back()->getName() << " has been successfully issued. ";
                            armies -= num_deploy;
                    }
                    else {
                            cout << "Invalid amount of armies entered. Order not successfully issued. " << endl;
                    }
                }
                break;
            case 2 :
                    cout << "Would you like to advance in order to... " << endl;
                    cout << " 1. Attack an enemy territory " << endl;
                    cout << " 2. Move troops between territories" << endl;
                    int attackOrMove;
                    cin >> attackOrMove;
                    if (attackOrMove == 1) {
                        vector<Territory *> *attack;
                        attack = toAttack(player, new Advance());
                        if (attack) {
                            Advance *a;
                            Territory *player_t = attack->front();//pop the player territory bordering an enemy's
                            Territory *enemy_t = attack->back(); //pop the enemy's territory
                            int num_armies;
                            cout << "How many armies would you like to attack with? " << endl;
                            cin >> num_armies;
                            a = new Advance(player, player_t, enemy_t, num_armies, deck);
                            player->getOrdersList()->add(a); //Attack it
                        }
                    }
                    else if (attackOrMove == 2){
                        vector<Territory *> *defend;
                        defend = toDefend(player, new Advance());
                        if (defend) {
                            Advance *a;
                            Territory *player_t = defend->back();
                            Territory *toMove_t = defend->front();
                            cout << "How many armies would you like to move from "
                            << *toMove_t->getName() << "?" << endl;
                            int num_armies;
                            cin >> num_armies;
                            a = new Advance(player, toMove_t, player_t, num_armies, deck);
                            player->getOrdersList()->add(a); //Attack it
                        }
                    }
                    break;
            case 3 :
                if (player->getHand()->playRound(deck, player)) {
                    cardPlayed = true;
                }
                break;
            default:
                cout << "Invalid choice.";
            }
            cout << "Issue another order? " << endl;
            cout << "1. Yes" << endl;
            cout << "2. No " << endl;
            int againOrNo;
            cin >> againOrNo;
            if (againOrNo == 1) {
                issueAgain = true;
            }
            else {
                issueAgain = false;
            }

    } while(issueAgain);
}
//Returns a territory to move troops from
Territory *HumanPlayerStrategy::toMove(Player *p) {
    Player *player = p;
    cout << "Please enter the ID of the territory you would like to move troops from :" << endl;
    int ID;
    cin >> ID;
    for (Territory *t : *player->getTerritories()) {
        if (t->getId() == ID) {
            return t;
        }
    }
    return nullptr;
}
Player *HumanPlayerStrategy::generateNegotiate() {
    cout << "Which of these players would you like to negotiate with?" << endl;
        int i = 1;
        for (Player *p: *players) {
            cout << i << " : " << *p << endl;
            i++;
        }
        int player_num;
        cin >> player_num;
        if (player_num > players->size() || player_num <= 0) {
            cout << "That is not a valid input. Order not successfully issued." << endl;
            return nullptr;

        }
        return players->at(player_num -1);
    }
//Returns vector containing one territory to defend.
vector<Territory *> *HumanPlayerStrategy::toDefend(Player *p, order *type) {
    Player *player = p;
    cout << "Here are your territories : " << endl;
    vector<Territory *> *territories = player->getTerritories();
    auto *toDefend = new vector<Territory *>();
    for (Territory *t : *territories) {
        cout << *t << endl;
    }
    if (dynamic_cast<Blockade *>(type) != nullptr) {
        cout << "Please enter the ID of the territory you would like to set up a blockade on." << endl;
    }
    else if (dynamic_cast<Deploy *>(type) != nullptr) {
        cout << "Please enter the ID of the territory you would like to reinforce." << endl;
    }
    else  {
        Territory *t = toMove(player);
        if (t) {
            toDefend->push_back(t);
        }
        else { return nullptr; }
        cout << "Please enter the ID of the territory you would like to move troops to." << endl;
    }
    int ID;
    cin >> ID;
    for (Territory *t : *territories) {
        if (t->getId() == ID) {
            toDefend->push_back(t);
            return toDefend;
        }
    }
    cout << "Invalid ID." << endl;
    return nullptr;
}
//Returns vector with front being territory to attack from, and back being territory to attack.
vector<Territory *> *HumanPlayerStrategy::toAttack(Player *p, order *type) {
    Player *player = p;
    auto *advance = dynamic_cast<Advance *>(type);
    if (advance) {
        cout << "Here are your territories with enemy territories bordering them : " << endl;
        displayToAdvance(player);
    }
    else {
        cout << "Here are the territories available to attack : " << endl;
        displayToAttack(player);
    }
    vector<Territory *> *territories = player->getTerritories();
    auto *toAttack = new vector<Territory *>();
    int ID;
    if (advance) {
        cout << "Please enter the ID of territory you are attacking from. " << endl;
        cin >> ID;
        for (Territory *t: *territories) {
            if (t->getId() == ID) {
                toAttack->push_back(t);
                cout << "Which of these enemy borders would you like to attack? " << endl;
                displayEnemyBorders(t, player);
                cout << "Please enter the ID : " << endl;
                cin >> ID;
                for (int i = 0; i < t->getEdgeCount(); i++) {
                    if (t->getEdges()[i]->getId() == ID) {
                        toAttack->push_back(t->getEdges()[i]);
                        return toAttack;
                    }
                }
            }
        }
    }
    else {
        cout << "Please enter the ID of the territory to bomb : " << endl;
        cin >> ID;
        for (Territory *t : *territories) {
            for (int i = 0; i < t->getEdgeCount(); i++) {
                if (t->getEdges()[i]->getId() == ID) {
                    toAttack->push_back(t);
                    toAttack->push_back(t->getEdges()[i]);
                    return toAttack;
                }
            }
        }
    }
    cout << "Invalid ID." << endl;
    return nullptr;
    }

void HumanPlayerStrategy::displayToAdvance(Player *p) {
    vector<Territory *> *territories = p->getTerritories();
    for (Territory *t: *territories) {
        Territory **borders = t->getEdges();
        bool hasEnemies = false;
        for (int i = 0; i < t->getEdgeCount(); i++) {
            Player *owner = borders[i]->getOwner();
            if (!owner || owner != p) {
                if (!hasEnemies) {
                    cout << endl;
                    cout << *t << endl;
                    cout << "ENEMY BORDERS :" << endl;
                    hasEnemies = true;
                }
                cout << "    " << *borders[i] << endl;
            }
        }
    }
}

void HumanPlayerStrategy::displayToAttack(Player *p) {
    vector<Territory *> *territories = p->getTerritories();
    auto *displayed = new vector<Territory *>();
    for (Territory *t: *territories) {
        Territory **borders = t->getEdges();
        for (int i = 0; i < t->getEdgeCount(); i++) {
            Player *owner = borders[i]->getOwner();
            if (!owner || owner != p) {
                Territory *enemy = borders[i];
                bool alreadyDisplayed = false;
                for (Territory *d : *displayed){
                    if (d == enemy) {
                        alreadyDisplayed = true;
                        break;
                    }
                }
                if (!alreadyDisplayed) {
                    cout << *borders[i] << endl;
                }
            }
        }
    }

}

void HumanPlayerStrategy::displayEnemyBorders(Territory *t, Player *p) {
    for (int i = 0; i < t->getEdgeCount(); i++) {
        Player *owner = t->getEdges()[i]->getOwner();
        if (!owner || owner != p) {
            cout << *t->getEdges()[i] << endl;
        }
    }
}


vector<Territory *> *AggressivePlayerStrategy::toAttack(Player *p, order *type) {
    Player *player = p;
    auto *out = new vector<Territory *>();
    for (Territory *t : *player->getTerritories()) {
        Territory ** borders = t->getEdges();
        for (int i = 0; i < t->getEdgeCount(); i++) {
            Player *owner = borders[i]->getOwner();
            if (!owner || owner != player) {
                out->push_back(t);
                out->push_back(borders[i]);
            }
        }
    }
    return out;
}

void AggressivePlayerStrategy::issueOrder(Player *p) {
    Player *player = p;
    Territory *strongest = toDefend(player, new Advance())->back();
    int armies = player->getArmies();
    player->getOrdersList()->add(new Deploy(player, strongest, armies));
    vector<Territory *> *targets = toAttack(player, new Advance());
    while (!targets->empty()) {
        Territory *enemy = targets->back();
        Territory *source = targets->at(targets->size()-2);
        player->getOrdersList()->add(new Advance(player, source, enemy, source->getNumberOfArmies(), deck));
        targets->pop_back();
        targets->pop_back();
    }
    player->getHand()->playCard(deck, player);
}



