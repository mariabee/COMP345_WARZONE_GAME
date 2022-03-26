//MAIN METHOD FOR TESTING
#include "Orders.h"
#include "../Part 2/Player.h"

int main(){
    Player *p1 = new Player("Cristina Yang");
    Player *p2 = new Player("Owen Hunt");
    Player *neutral = new Player("Neutral");
    auto *t1 = new Territory(1, "Seattle Grace Hospital", nullptr);
    auto *t2 = new Territory(2, "Grey Sloan Memorial", nullptr);
    auto *t3 = new Territory(3, "Denny Duquette Clinic", nullptr);
    Deck* gameDeck = new Deck();
    cout << "There are currently " << gameDeck->getCurrentSize() << " cards in the deck. \n";
    p1->getHand()->drawFromDeck(gameDeck);
    p1->getHand()->drawFromDeck(gameDeck);
    p1->getHand()->drawFromDeck(gameDeck);
    p1->getHand()->drawFromDeck(gameDeck);
    p1->getHand()->drawFromDeck(gameDeck);


    //Deploy order
    t1->changeOwner(p1);
    p1->setArmies(5);
    //Deploy 5 armies from Cristina's pool to Seattle Grace Hospital
    auto *deploy = new Deploy(p1,t1,5);
    deploy->execute();
    //Try again with Christina having 0 armies now
    auto *deploy01 = new Deploy(p1,t1,5);
    deploy01->execute();

    //Advance Order
    t2->changeOwner(p1);
    t3->changeOwner(p2);
    //Advancing 4 armies from Seattle Grace to Grey Sloan
    auto *advance = new Advance(p1,t1,t2,4);
    advance->execute();
    //Owen attacking
    t3->setNumberOfArmies(1);
    auto *advance01 = new Advance(p2,t3,t2,1);
    advance01->execute();
    //Attacking Owen
    t3->setNumberOfArmies(1);
    t2->setNumberOfArmies(4);
    auto *advance02 = new Advance(p1,t2,t3,4);
    advance02->execute();



}


