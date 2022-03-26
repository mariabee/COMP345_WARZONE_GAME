#include "Cards.h"
#include<iostream>

using namespace std;

// ___________________
// Class Card methods
// ___________________
//constructor
Card::Card(){
    switch ( rand() % 5 ) {
        case 1:
            type = BOMB;
            break;
        case 2:
            type = REINFORCEMENT;
            break;
        case 3:
            type = BLOCKADE;
            break;
        case 4:
            type = AIRLIFT;
            break;
        case 0:
            type = DIPLOMACY;
            break;
    }
}
//Card constructor of specific type
Card::Card(cardType t){
    type = t;
}
//copy constructor
Card::Card(const Card & obj){
    type = obj.type;
}

//destructor
Card::~Card(){

}

//assignment operator overloading
void Card::operator = (const Card & card)
{
    type = card.type;
}

//stream insertion overloading (print card)
std::ostream &operator << ( std::ostream &out, const Card &card ){
    switch ( card.type ) {
        case BOMB:
            out << "BOMB\n";
            break;
        case REINFORCEMENT:
            out << "REINFORCEMENT\n";
            break;
        case BLOCKADE:
            out << "BLOCKADE\n";
            break;
        case AIRLIFT:
            out << "AIRLIFT\n";
            break;
        case DIPLOMACY:
            out << "DIPLOMACY\n";
            break;
    }
    return out;
}

//Different effects of the cards based on their type
void Card::play(Deck* deck, Player* player, Player *other)
{
    Territory *source = player->toAttack()->at(0);
    Territory *target = player->toAttack()->at(1);
    Territory *toMove = player->getToMove()->at(0);
    switch ( type ) {
        case BOMB:
            cout << "You PLAYED your BOMB card\n";
            player->issueOrder(new Bomb(player, source, target));
            break;
        case REINFORCEMENT:
            cout << "You PLAYED your REINFORCEMENT card\n";
            player->issueOrder(new Deploy(player, source, 3));
            break;
        case BLOCKADE:
            cout << "You PLAYED your BLOCKADE card\n";
            player->issueOrder(new Blockade(player, source, nullptr));
            break;
        case AIRLIFT:
            cout << "You PLAYED your AIRLIFT card\n";
            player->issueOrder(new Airlift(player, toMove, source, toMove->getNumberOfArmies()));
            break;
        case DIPLOMACY:
            cout << "You PLAYED your DIPLOMACY card\n";
            player->issueOrder(new Negotiate(player, other));
            break;
    }
    deck->addCardBackToDeck(this);
}


// ___________________
// Class Deck methods
// ___________________

//Default Constructor
Deck::Deck()
{
    initialDeckSize = 55;
    nbCardInDeck = initialDeckSize;
    cardsInDeck = new Card*[initialDeckSize];
    initialDeck = new Card[initialDeckSize];

    this->initialize();

    cout << "Deck object were successfully CREATED\n";
}

//Deck Constructor of specific size
Deck::Deck(int deckSize)
{
    initialDeckSize = deckSize;
    while (nbCardInDeck < 0){
        cout << "Not a valid deck size; The deck size is there initiated with 55 cards.\n";
        initialDeckSize = 55;
    }
    nbCardInDeck = initialDeckSize;
    cardsInDeck = new Card*[initialDeckSize];
    initialDeck = new Card[initialDeckSize];

    this->initialize();

//    cout << "Deck object were successfully CREATED\n";
}
//copy constructor
Deck::Deck(const Deck &obj){
    Card** cardsInDeck = new Card*[initialDeckSize];
    Card* initialDeck = new Card[initialDeckSize];

    **cardsInDeck = **obj.cardsInDeck;
    *initialDeck = *obj.initialDeck;
    initialDeckSize = obj.initialDeckSize;
    nbCardInDeck = obj.nbCardInDeck;

    cout << "Deck object were successfully CREATED\n";
}

//destructor
Deck::~Deck()
{
    delete[] cardsInDeck;
    cardsInDeck = nullptr;
    delete[] initialDeck;
    initialDeck = nullptr;
    cout << "Deck object were successfully DELETED\n";
}

//assignment operator overloading
void Deck::operator = (const Deck & deck){
    **cardsInDeck = **deck.cardsInDeck;
    *initialDeck = *deck.initialDeck;
    initialDeckSize = deck.initialDeckSize;
    nbCardInDeck = deck.nbCardInDeck;
}

//stream insertion overloading (print deck)
std::ostream &operator << ( std::ostream &out, const Deck &deck ){
    for( int i = 0 ; i < deck.nbCardInDeck; i++ ){
        out << "Card #" << i+1 << " " << deck.cardsInDeck[i];
    }
    return out;
}

//Create all the Cards object in the deck
void Deck::initialize (){
    for (int i = 0 ; i < initialDeckSize ; i ++){
        Card c1 = Card();
        initialDeck[i] = c1;
        cardsInDeck[i] = &initialDeck[i];
    }
}

//Get number of card not in a players hand
int Deck::getCurrentSize()
{
    return nbCardInDeck;
}

//Put cards back in the deck when it's played
void Deck::addCardBackToDeck(Card* card)
{
    for (int i = 0 ; i < nbCardInDeck; i++ ){
        if (cardsInDeck[i] == nullptr){
            cardsInDeck[i] = card;
            this->nbCardInDeck ++;
            cout << "Card was successfully placed back in the deck";
            break;
        }
    }
}

//Draw card from the deck
Card* Deck::draw()
{
    Card* pickedCard ;

    while( nbCardInDeck > 0 ){
        int temp = rand() % initialDeckSize;
        pickedCard = cardsInDeck[temp];
        if (pickedCard != nullptr) {
            cardsInDeck[temp] = nullptr;
            this->nbCardInDeck--;
            cout << "You've just received this NEW CARD: \n" << *pickedCard;
            return pickedCard;
        }
    }
    cout << "The deck is empty";
    return nullptr;
}

//____________________
// Class Hand methods
// ___________________
//constructor
Hand::Hand(){
    nbCardsInHand = 0;
    maxCard = 5;
    cardsInHand = new Card*[maxCard]();
//    cout << "Hand object were successfully CREATED\n";
}
//copy constructor
Hand::Hand(const Hand &obj){
    Card** cardsInHand = new Card*[maxCard]();
    *cardsInHand = *obj.cardsInHand;
    maxCard = obj.maxCard;
    nbCardsInHand = obj.nbCardsInHand;
    cout << "Hand object were successfully CREATED\n";
}

//destructor
Hand::~Hand(){
    delete[] cardsInHand;
    cardsInHand = nullptr;
    cout << "Hand object were successfully DELETED\n";
}

//assignment operator overloading
void Hand::operator = (const Hand & hand){
    *cardsInHand = *hand.cardsInHand;
    maxCard = hand.maxCard;
    nbCardsInHand = hand.nbCardsInHand;
}

// Draw a card from the deck (add a card in hand)
void Hand::drawFromDeck(Deck* deck){
    if (nbCardsInHand == maxCard){
        cout << "Your hand is full. You currently have " << nbCardsInHand << " cards.\n";
    }
    else{
        for (int i = 0 ; i < maxCard; i++ ){
            if (cardsInHand[i] == nullptr){
                cardsInHand[i] = deck->draw();
                nbCardsInHand++;
                break;
            }
        }
    }
}

//Play a card in the hand and return it in the deck
void Hand::playRound(Deck* deck, Player* player)
{
    if (nbCardsInHand == 0){
        cout << "You don't have any card in your hand at the moment.\n";
    }
    else{
        //Print out of all the cards in hand
        cout << "\nHere are the cards you have in your hand: \n" << *this;

        //Ask user which card they would like to play
        cout << "\n\nEnter the position of the card you would like to play (1 for the first card printed). " <<
                "Enter 0 if would like to play your turn with no card: \n";
        int cardChoice;
        cin >> cardChoice;

        //Invalid input results in no cards being played
        if (cardChoice > 0 && cardChoice <= nbCardsInHand) {
            cardsInHand[cardChoice-1]->play(deck, player);
            for(int i = cardChoice-1; i < maxCard; i++){
                cardsInHand[i] = cardsInHand[i+1];
            }
            nbCardsInHand--;
        }
        cout << "\n\n";
    }
}

// Print all the cards in hand
std::ostream &operator << (std::ostream &out, const Hand &hand ){
    for( int i = 0 ; i < hand.nbCardsInHand ; i++ ){
        out << "\nCard #" << i+1 << " " << *hand.cardsInHand[i];
    }
    return out;
}