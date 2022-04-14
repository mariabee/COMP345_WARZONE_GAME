#ifndef COMP345_CARD_H
#define COMP345_CARD_H

#include <iostream>
//for randomness
#include <stdlib.h>
#include <time.h>

#include "../Part 2/Player.h"

class Deck;
class Hand;
enum cardType {BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY }; // Type possible for a give card

class Card {
private:
    cardType type; // Type of the give card

public:
    //constructor
    Card();
    Card(cardType t);
    Card(const Card &obj);

    //destructor
    ~Card();

    //assignment operator overloading
    Card& operator = (const Card & card);

    //stream insertion overloading (print card)
    friend std::ostream &operator << ( std::ostream &out, const Card &card );

    //play a card (will be more useful when we use it with the player part)
    bool play(Deck* deck, Player* player);

};


class Deck {

private:
    int nbCardInDeck; // Number of cards in the deck
    int initialDeckSize; // Number of cards in the game
    Card** cardsInDeck; // Array of the cards in the deck
    Card* initialDeck; // Array of all the card of the game

public:
    //constructor
    Deck();
    Deck(int deckSize);
    Deck(const Deck &obj);

    //destructor
    ~Deck();

    //assignment operator overloading
    Deck& operator = (const Deck & deck);

    //stream insertion overloading (print deck)
    friend std::ostream &operator << ( std::ostream &out, const Deck &deck );

    //create all the Cards object in the deck
    void initialize();

    //get number of card not in a players hand
    int getCurrentSize() const;

    //put cards back in the deck when it's played
    void addCardBackToDeck(Card *card);

    //draw card from the deck
    Card* draw();

};


class Hand{

private:
    int nbCardsInHand; //number of cards in hand
    int maxCard; // maximum nb of cards a play can hold
    Card** cardsInHand; //array of cards in hand

public:
    //constructor
    Hand();
    Hand(const Hand &obj);

    //destructor
    ~Hand();

    //assignment operator overloading
    Hand& operator = (const Hand & hand);

    //draw a card from the deck (add a card in hand)
    void drawFromDeck(Deck* deck);

    //play a card in the hand and return it in the deck
    bool playRound(Deck* deck, Player* player);
    void playCard(Deck *deck, Player* player, int i);

    //stream insertion operator overloading(print list of cards in hand)
    friend std::ostream &operator << ( std::ostream &out, const Hand &hand );
};


#endif //COMP345_CARD_H