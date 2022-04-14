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

Player *PlayerStrategy::generateNegotiate(Player *p) {
    for (Player *other : *players) {
        if (other != p) {
            return other;
        }
    }
    return nullptr;
}

HumanPlayerStrategy::HumanPlayerStrategy() = default;

bool HumanPlayerStrategy::issueOrder(Player *player, order *o) {
        if (dynamic_cast<Negotiate *>(o)) {
            auto *negotiate  = dynamic_cast<Negotiate *>(o);
            Player *p = generateNegotiate(player);
            if (!p) return false;
            negotiate->setPlayer2(p);
            negotiate->set_player(player);
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
Player *HumanPlayerStrategy::generateNegotiate(Player *p) {
    cout << "Which of these players would you like to negotiate with?" << endl;
        int i = 1;
        int skip = 0;
        for (Player *other: *players) {
            if (other != p) {
                cout << i << " : " << *p << endl;
                i++;
            }
            else {
                skip = i;
            }
        }
        int player_num;
        cin >> player_num;
        if (player_num > players->size() || player_num <= 0) {
            cout << "That is not a valid input. Order not successfully issued." << endl;
            return nullptr;

        }
        if (player_num >= skip) {
            player_num++;
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
//Returns vector with back being territory to attack, and next being territory to attack from.
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
//Displays player territories and their enemy/neutral borders
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
//Displays all enemy/neutral territories available for a player to attack
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
//Displays all enemy borders of a player's territory
void HumanPlayerStrategy::displayEnemyBorders(Territory *t, Player *p) {
    for (int i = 0; i < t->getEdgeCount(); i++) {
        Player *owner = t->getEdges()[i]->getOwner();
        if (!owner || owner != p) {
            cout << *t->getEdges()[i] << endl;
        }
    }
}
///////////////////////////////AGGRESSIVE PLAYER/////////////////////////

//Returns vector with back being territory to attack, and next being territory to attack from.
vector<Territory *> *AggressivePlayerStrategy::toAttack(Player *p, order *type) {
    Player *player = p;
    auto *out = new vector<Territory *>();
    for (Territory *t : *player->getTerritories()) {
        if (dynamic_cast<Advance *>(type) && t->getNumberOfArmies() <= 0) {
            continue;
        }
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

void AggressivePlayerStrategy::issueOrder(Player *player) {
    Territory *strongest = toDefend(player, new Advance())->back();
    int armies = player->getArmies();
    vector<Territory *> *targets = toAttack(player, new Advance());
    int n = targets->size();
    if (n > 0) {
        cout << *player->getName() << " has issued order(s) to attack " << n/2 << " territories." << endl;
        n = 0;
    }
    else {
        Territory *border = strongest->getEdges()[0];
        if (previous && border == previous) {
            if (strongest->getEdgeCount() > 1) {
                border = strongest->getEdges()[1];
            }
        }
        auto *a = new Advance(player, strongest, border, strongest->getNumberOfArmies() + armies, deck);
        previous = strongest;
        strongest = border;
        player->getOrdersList()->add(a);
        n = 1;
    }
    player->getOrdersList()->add(new Deploy(player, strongest, armies));
    while (!targets->empty()) {
        Territory *enemy = targets->back();
        Territory *source = targets->at(targets->size()-2);
        int max_attack = enemy->getNumberOfArmies() + 3;
        auto *a = new Advance(player, source, enemy, max_attack, deck);
        player->getOrdersList()->add(a);
        targets->pop_back();
        targets->pop_back();
    }
    for (int i = 0; i < strongest->getEdgeCount(); i++) {
        Territory *border = strongest->getEdges()[i];
        Player *owner = border->getOwner();
        if (owner && owner == player && border->getNumberOfArmies() > 0) {
            auto *a = new Advance(player, border, strongest, border->getNumberOfArmies(), deck);
            n++;
            player->getOrdersList()->add(a);
        }
    }
    if (n > 0) {
        cout << *player->getName() << " has issued orders to move troops from " << n << " territories. " << endl;
    }
    player->getHand()->playCard(deck, player, 0);
}

vector<Territory *> *AggressivePlayerStrategy::toDefend(Player *p, order *type) {
    if (dynamic_cast<Blockade *>(type)) {
        return nullptr;
    }
    auto *out = new vector<Territory *>();
    Territory *strongest = nullptr;
    Territory *past_strong = nullptr;
    int max_armies = 0;
    for (Territory *t : *p->getTerritories()) {
        if (t->getNumberOfArmies() > max_armies) {
            max_armies = t->getNumberOfArmies();
            past_strong = strongest;
            strongest = t;
        }
        else if (t->getNumberOfArmies() == max_armies) {
            if (!strongest || t->getEdgeCount() > strongest->getEdgeCount()) {
                past_strong = strongest;
                strongest = t;
            }
        }
    }
    out->push_back(strongest);
    if (dynamic_cast<Airlift *>(type)) {
        if (past_strong) {
            out->push_back(past_strong);
        }
        else {
            return nullptr;
        }
    }
    return out;
}

bool AggressivePlayerStrategy::issueOrder(Player *p, order *o) {
    if (dynamic_cast<Negotiate *>(o) || dynamic_cast<Blockade *>(o)) {
        return false;
    }
    else {
        p->getOrdersList()->add(o);
    }
    return true;
}


AggressivePlayerStrategy::AggressivePlayerStrategy() {
    previous = nullptr;
};


vector<Territory *> *BenevolentPlayerStrategy::toAttack(Player *p, order *type) {
    return nullptr;
}
vector<Territory *> *BenevolentPlayerStrategy::toDefend(Player *p, order *type) {
    auto *out = new vector<Territory *>();
    Territory *weakest = nullptr;
    Territory *past_weak = nullptr;
    int min_armies = 0;
    for (Territory *t : *p->getTerritories()) {
        if(weakest == nullptr){
            weakest=t;
        }
        else if(t->getNumberOfArmies() == min_armies){
            past_weak = weakest;
            weakest = t;
        }
        else if(t->getNumberOfArmies()< weakest->getNumberOfArmies()){
            past_weak = weakest;
            weakest = t;
        }
    }
    out->push_back(weakest);
    if (dynamic_cast<Airlift *>(type)) {
        if (past_weak) {
            out->push_back(past_weak);
        }
        else {
            return nullptr;
        }
    }
    return out;

}

bool BenevolentPlayerStrategy::issueOrder(Player *p, order *o) {
    if (auto *negotiate  = dynamic_cast<Negotiate *>(o)) {
        Player *other = generateNegotiate(p);
        if (!other) return false;
        negotiate->setPlayer2(other);
        negotiate->set_player(p);
        p->getOrdersList()->add(negotiate);
    }else if(auto *bomb  = dynamic_cast<Bomb *>(o)){
        cout<<"A BENEVOLENT PLAYER CANNOT BOMB TERRITORIES";
        return false;
    }
    else{
        p->getOrdersList()->add(o);
    }
    return true;
}

void BenevolentPlayerStrategy::issueOrder(Player *p) {
    while(!toDefend(p, new Advance)->empty()) {
        Territory *weakest = toDefend(p, new Advance)->back();
        cout << "BENEVOLENT PLAYER HAS ISSUED A DEPLOY ON" << toDefend(p, new Advance)->back();
        toDefend(p, new Advance)->pop_back();
        p->getOrdersList()->add(new Deploy(p, weakest, p->getArmies()));
    }
}
BenevolentPlayerStrategy::BenevolentPlayerStrategy() = default;


///////////////////////////////CHEATER PLAYER/////////////////////////

//TODO: ADD SOMETHING IN ADVANCE THAT ALWAYS MAKES THE CHEATER WIN
vector<Territory *> *CheaterPlayerStrategy::toAttack(Player *p, order *type) {
    auto *out = new vector<Territory *>();
    for (Territory *t : *p->getTerritories()) {
        if (dynamic_cast<Advance *>(type)){
            Territory ** borders = t->getEdges();
            for (int i = 0; i < t->getEdgeCount(); i++) {
                Player *owner = borders[i]->getOwner();
                if (owner != p) {
                    out->push_back(t);
                    out->push_back(borders[i]);
                }
            }
        }
    }
    return out;
}

vector<Territory *> *CheaterPlayerStrategy::toDefend(Player *p, order *type) {
    return nullptr;
}

bool CheaterPlayerStrategy::issueOrder(Player *p, order *o) {
    if (auto *negotiate  = dynamic_cast<Negotiate *>(o)) {
        Player *other = generateNegotiate(p);
        if (!other) return false;
        negotiate->setPlayer2(other);
        negotiate->set_player(p);
        p->getOrdersList()->add(negotiate);
    }
    else{
        p->getOrdersList()->add(o);
    }
    return true;

}

void CheaterPlayerStrategy::issueOrder(Player *p) {
    while (!toAttack(p, new Advance)->empty()) {
        Territory *source = toAttack(p,new Advance)->back();
        toAttack(p,new Advance)->pop_back();
        Territory *edge =  toAttack(p,new Advance)->back();
        toAttack(p,new Advance)->pop_back();
        p->getOrdersList()->add(new Advance(p, source,edge, 0, deck));
    }
}

CheaterPlayerStrategy::CheaterPlayerStrategy() = default;


///////////////////////////////NEUTRAL PLAYER/////////////////////////

NeutralPlayerStrategy::NeutralPlayerStrategy() = default;
bool NeutralPlayerStrategy::issueOrder(Player *p, order *o) {
    return false;
}
void NeutralPlayerStrategy::issueOrder(Player *p) {}
vector<Territory *> *NeutralPlayerStrategy::toDefend(Player *p, order *type) {
    return nullptr;
}
vector<Territory *> *NeutralPlayerStrategy::toAttack(Player *p, order *type) {
    return nullptr;
}
