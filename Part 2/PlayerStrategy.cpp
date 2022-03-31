#include "PlayerStrategy.h"


HumanPlayerStrategy::HumanPlayerStrategy() = default;

void HumanPlayerStrategy::issueOrder(Player *player, order *o) {
        if (dynamic_cast<Negotiate *>(o) != nullptr) {
            Negotiate *negotiate  = dynamic_cast<Negotiate *>(o);
            bool invalid = false;
            do {
                cout << "Which of these players would you like to negotiate with?" << endl;
                int i = 1;
                for (Player p: *players) {
                    cout << i << " : " << p << endl;
                    i++;
                }
                int player_num;
                cin >> player_num;
                if (player_num >= players->size() || player_num <= 0) {
                    cout << "That is not a valid input. Please try again!" << endl;
                    invalid = true;
                } else {
                    negotiate->setPlayer2(&players->at(player_num -1));
                    player->getOrdersList()->add(negotiate);
                    invalid = false;
                }
            } while(invalid);
        }
        else {
            player->getOrdersList()->add(o);
        }
}
void HumanPlayerStrategy::issueOrder(Player *p) {
    bool issueAgain;
    Player *player = p;
    int armies = player->getArmies();
    do {
        cout << "Please select which order to issue : " << endl;
        cout << "1. Deploy troops " << endl;
        cout << "2. Advance troops " << endl;
        cout << "3. Play a card " << endl;
        int n;
        cin >> n;
        vector<Territory *> *territories = player->getTerritories();
        switch(n) {
            case 1:
                cout << "Here are all the territories you own : " << endl;
                for (Territory *t : *territories) {
                    cout << *t << endl;
                }
                cout << "Please enter the ID of the territory you would like to deploy troops to :" << endl;
                int ID;
                bool validID;
                cin >> ID;
                for (Territory *t : *territories) {
                    if (ID == t->getId()) {
                        validID = true;
                        cout << "You have " << armies << " troops available. How many troops would you like to deploy ? " << endl;
                        int n;
                        cin >> n;
                        if (n <= armies && armies < 0) {
                            player->getOrdersList()->add(new Deploy(player, t, n));
                            cout << "Order to deploy " << n << " troops " << " to " << *t->getName()
                                 << " has been successfully issued.";
                            armies -= n;
                        }
                        else {
                            cout << "Invalid amount of armies entered. Order not successfully issued. " << endl;
                        }
                        break;
                    }
                }
                if (!validID) {
                    cout << "Order was not issued due to invalid ID input." << endl;
                }
                break;
            case 2 :
                    cout << "Would you like to advance in order to... " << endl;
                    cout << " 1. Attack an enemy territory " << endl;
                    cout << " 2. Move troops between territories" << endl;
                    int attackOrMove;
                    cin >> attackOrMove;
                    if (attackOrMove == 1) {
                        vector<Territory *> *toAttack = toAttack;
                        Territory *player_t = toAttack->front();//pop the player territory bordering an enemy's
                        Territory *enemy_t = toAttack->back(); //pop the enemy's territory
                        int num_armies;
                        cout << "How many armies would you like to attack with? " << endl;
                        cin >> num_armies;
                        player->getOrdersList()->add(new Advance(player, player_t, enemy_t, num_armies, deck)); //Attack it
                    }
                    else if (attackOrMove == 2){
                        vector<Territory *> *toDefend = toDefend;
                        Territory *player_t = toDefend->back();
                        Territory *toMove_t = toMove(player);
                        cout << "How many armies would you like to move from " << *toMove_t->getName() << "?" << endl;
                        int num_armies;
                        cin >> num_armies;
                        player->getOrdersList()->add(new Advance(player, toMove_t, player_t, num_armies, deck)); //Attack it
                    }
                    else {
                        cout << "Invalid choice. Order was not successfully issued. " << endl;
                    }
                    break;
            case 3 :
                player->getHand()->playRound(deck, player);
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
    cout << "Here are your territories : " << endl;
    vector<Territory *> *territories = player->getTerritories();
    for (Territory *t : *territories) {
        cout << *t << endl;
    }
    cout << "Please enter the ID of the territory you would like to move troops from :" << endl;
    int ID;
    cin >> ID;
    for (Territory *t : *territories) {
        if (t->getId() == ID) {
            return t;
        }
    }
    return nullptr;
}
//Returns vector containing one territory to defend.
vector<Territory *> *HumanPlayerStrategy::toDefend(Player *p) {
    Player *player = p;
    cout << "Here are your territories : " << endl;
    vector<Territory *> *territories = player->getTerritories();
    vector<Territory *> *toDefend;
    for (Territory *t : *territories) {
        cout << *t << endl;
    }
    cout << "Please enter the ID of the territory you would like to defend." << endl;
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
vector<Territory *> *HumanPlayerStrategy::toAttack(Player *p) {
    Player *player = p;
    cout << "Here are your territories with enemy territories bordering them : " << endl;
    vector<Territory *> *territories = player->getTerritories();
    vector<Territory *> *toAttack;
    for (Territory *t : *territories) {
        cout << *t << endl;
        Territory **borders = t->getEdges();
        cout << "ENEMY BORDERS :" << endl;
        bool hasEnemies = false;
        for (int i =0 ; i < t->getEdgeCount(); i++) {
            if (borders[i]->getOwner() != player) {
                cout << "    " << *borders[i] << endl;
                hasEnemies = true;
            }
        }
        if (!hasEnemies) {
            cout << *t->getName() << " has no enemies bordering it." << endl;
        }
    }
    cout << "Please enter the ID of territory you are attacking from. " << endl;
    int ID;
    cin >> ID;
    bool validID = false;
    for (Territory *t : *territories) {
        if (t->getId() == ID) {
            toAttack->push_back(t);
            validID = true;
            cout << "Which of these enemy borders would you like to attack? " << endl;
            for (int i = 0; i < t->getEdgeCount(); i++) {
                if (t->getEdges()[i]->getOwner() == player) {
                    cout << t->getEdges()[i] << endl;
                }
            }
            cout << "Please enter the ID : " << endl;
            cin >> ID;
            for (int i = 0; i < t->getEdgeCount(); i++) {
                if (t->getEdges()[i]->getId() == ID) {
                    toAttack->push_back(t->getEdges()[i]);
                    return toAttack;
                }
            }
            validID = false;
        }
    }
    if (!validID)  {
        cout << "Invalid ID." << endl;
    }
    return nullptr;
    }

AggressivePlayerStrategy::AggressivePlayerStrategy() {
}

void AggressivePlayerStrategy::issueOrder(Player *p, order *o) {
    Player *player = p;
    Territory *strongest = toDefend(player)->back();
    int armies = player->getArmies();
    player->getOrdersList()->add(new Deploy(player, strongest, armies));
    vector<Territory *> *targets = toAttack(player);
    while (!targets->empty()) {
        Territory *enemy = targets->back();
        Territory *source = targets->at(targets->size()-2);
        player->getOrdersList()->add(new Advance(player, source, enemy, source->getNumberOfArmies(), deck));
        targets->pop_back();
        targets->pop_back();
    }
    player->getHand()->playCard(deck, player);
}

Territory *AggressivePlayerStrategy::toMove(Player *p) {
    return nullptr;
}

vector<Territory *> *AggressivePlayerStrategy::toDefend(Player *p) {
    Player *player = p;
    int strong_armies = 0;
    int current_armies;
    Territory *strongest = nullptr;
    vector<Territory *> *out;
    for (Territory *t : *player->getTerritories()) {
        current_armies = t->getNumberOfArmies();
        if (current_armies > strong_armies) {
            strongest = t;
            strong_armies = current_armies;
        }
        else if (current_armies == strong_armies) {
            if (!strongest || t->getEdgeCount() > strongest->getEdgeCount()) {
                strongest = t;
                strong_armies = current_armies;
            }
        }
    }
    out->push_back(strongest);
    return out;
}

vector<Territory *> *AggressivePlayerStrategy::toAttack(Player *p) {
    Player *player = p;
    vector<Territory *> *out;
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

