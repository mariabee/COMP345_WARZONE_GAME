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

Card::Card(cardType t){
    type = t;
}

//destructor
Card::~Card(){

}

//Print card
void Card::printCard()
{
    switch ( type ) {
        case BOMB:
            cout << "BOMB\n";
            break;
        case REINFORCEMENT:
            cout << "REINFORCEMENT\n";
            break;
        case BLOCKADE:
            cout << "BLOCKADE\n";
            break;
        case AIRLIFT:
            cout << "AIRLIFT\n";
            break;
        case DIPLOMACY:
            cout << "DIPLOMACY\n";
            break;
    }
}

//Different effects of the cards based on their type
void Card::play()
{
    switch ( type ) {
        case BOMB:
            cout << "You PLAYED your BOMB card\n";
            break;
        case REINFORCEMENT:
            cout << "You PLAYED your REINFORCEMENT card\n";
            break;
        case BLOCKADE:
            cout << "You PLAYED your BLOCKADE card\n";
            break;
        case AIRLIFT:
            cout << "You PLAYED your AIRLIFT card\n";
            break;
        case DIPLOMACY:
            cout << "You PLAYED your DIPLOMACY card\n";
            break;
    }
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

    for (int i = 0 ; i < initialDeckSize ; i ++){
        Card c1 = Card();
        initialDeck[i] = c1;
        cardsInDeck[i] = &initialDeck[i];
    }
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

//Get number of card not in a players hand
int Deck::getCurrentSize()
{
    return nbCardInDeck;
}

//Put cards back in the deck when it's played
void Deck::addCardBackToDeck(Card* card)
{
    for (int i = 0 ; i < nbCardInDeck; i++ ){
        if (cardsInDeck[i] == NULL){
            cardsInDeck[i] = card;
            nbCardInDeck ++;
            break;
        }
    }
}

//Draw card from the deck
Card* Deck::draw()
{
    Card* pickedCard ;

    while( nbCardInDeck > 0 ){
        pickedCard = cardsInDeck[rand() % initialDeckSize];
        if (pickedCard != nullptr) {
            this->nbCardInDeck--;
            cout << "You've just received this NEW CARD: \n";
            pickedCard->printCard();
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
    cardsInHand = new Card*[maxCard];
    cout << "Hand object were successfully CREATED\n";
}

//destructor
Hand::~Hand(){
    delete[] cardsInHand;
    cardsInHand = nullptr;
    cout << "Hand object were successfully DELETED\n";
}

// Draw a card from the deck (add a card in hand)
void Hand::drawFromDeck(Deck* deck){
    if (nbCardsInHand == maxCard){
        cout << "Your hand is full. You currently have " << nbCardsInHand << " cards.\n";
    }
    else{
        for (int i = 0 ; i < maxCard; i++ ){
            if (cardsInHand[i] == NULL){
                cardsInHand[i] = deck->draw();
                nbCardsInHand++;
                break;
            }
        }
    }
}

//Play a card in the hand and return it in the deck
void Hand::playRound(Deck* deck)
{
    if (nbCardsInHand == 0){
        cout << "You don't have any card in your hand at the moment.\n";
    }
    else{
        //Print out of all the cards in hand
        cout << "\nHere are the cards you have in your hand: \n";
        printHand();

        //Ask user which card they would like to play
        cout << "\n\nEnter the position of the card you would like to play (1 for the first card printed). " <<
                "Enter 0 if would like to play your turn with no card: \n";
        int cardChoice;
        cin >> cardChoice;

        //Invalid input results in no cards being played
        if (cardChoice > 0 && cardChoice < nbCardsInHand) {
            cardsInHand[cardChoice-1]->play();
            deck->addCardBackToDeck(cardsInHand[cardChoice-1]);
            for(int i = cardChoice-1; i < maxCard; i++){
                cardsInHand[i] = cardsInHand[i+1];
            }
            nbCardsInHand--;
        }
        cout << "\n\n";
    }
}

// Print all the cards in hand
void Hand::printHand()
{
    for( int i = 0 ; i < nbCardsInHand ; i++ ){
        cout << "Card #" << i+1 << " ";
        cardsInHand[i]->printCard();
    }
}




