#ifndef COMP345_CARD_H
#define COMP345_CARD_H

//for randomness
#include <stdlib.h>
#include <time.h>


enum cardType { BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY }; // Type possible for a give card


class Card {
private:
    cardType type; // Type of the give card

public:
    //constructor
    Card();
    Card(cardType t);

    //destructor
    ~Card();

    //play a card (will be more useful when we use it with the player part)
    void play();

    //print
    void printCard();

};


class Deck: public Card {

private:
    int nbCardInDeck; // Number of cards in the deck
    int initialDeckSize; // Number of cards in the game
    Card** cardsInDeck; // Array of the cards in the deck
    Card* initialDeck; // Array of all the card of the game


public:
    //constructor
    Deck();
    Deck(int deckSize);

    //destructor
    ~Deck();

    //Get number of card not in a players hand
    int getCurrentSize();

    //Put cards back in the deck when it's played
    void addCardBackToDeck(Card* card);

    //Draw card from the deck
    Card* draw();

};


class Hand: public Card{

private:
    int nbCardsInHand; //number of cards in hand
    int maxCard; // maximum nb of cards a play can hold
    Card** cardsInHand; //array of cards in hand

public:
    //constructor
    Hand();
    // destructor
    ~Hand();
    // Draw a card from the deck (add a card in hand)
    void drawFromDeck(Deck* deck);

    //Play a card in the hand and return it in the deck
    void playRound(Deck* deck);

    //Print list of cards in hand
    void printHand();
};


#endif //COMP345_CARD_H
