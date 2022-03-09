// #include<iostream>
// #include "Cards.h"
// #include "../Part 2/Player.h"

// using namespace std;

// int main()
// {
//     //Setting the random seed
//     time_t t;
//     srand((unsigned) time(&t));


//     cout << "\n\n\nPART 4: Cards, Deck and Hand\n\n";

//     //Create Deck of card (and therefore initialize the cards with all 5 types).
//     Deck* gameDeck = new Deck();

//     //test method to get the size of the deck
//     cout << "There are currently " << gameDeck->getCurrentSize() << " cards in the deck. \n";

//     Player *p1 = new Player("Jane Doe");
//     //Create a hand object that will try and pick 6 cards
//     Hand* playerHand = p1->getHand();

//     cout << "\n\n*** Trying to play a card when none have been given yet\n";
//     playerHand->playRound(gameDeck,p1); // Throws Empty Deck Message

//     cout << "\n\n*** Drawing 6 cards from the deck \n";
//     playerHand->drawFromDeck(gameDeck);
//     playerHand->drawFromDeck(gameDeck);
//     playerHand->drawFromDeck(gameDeck);
//     playerHand->drawFromDeck(gameDeck);
//     playerHand->drawFromDeck(gameDeck);
//     playerHand->drawFromDeck(gameDeck); //Throws Error Message;

//     //Hand plays a card
//     cout << "\n\n*** Playing 3 cards\n";
//     playerHand->playRound(gameDeck,p1);
//     playerHand->playRound(gameDeck,p1);
//     playerHand->playRound(gameDeck,p1);

//     //Test method to get the size of the deck
//     cout << "There are now " << gameDeck->getCurrentSize() << " cards in the deck. \n";

//     // Delete pointers and the various object
//     delete gameDeck;
//     delete playerHand;

//     return 0;
// }