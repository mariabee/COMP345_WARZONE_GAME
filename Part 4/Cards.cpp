#include "Cards.h"
#include<iostream>
#include "Player.h"
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
Card::~Card() = default;

//assignment operator overloading
Card& Card::operator = (const Card & card)
{
    if (this == &card) {
        return *this;
    }
    type = card.type;
    return *this;
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
bool Card::play(Deck* deck, Player* player)
{
    Territory *source;
    Territory *target;
    vector <Territory *> *toAttack;
    vector <Territory *> *toDefend;
    bool cardPlayed = true;
        switch (type) {
            case BOMB:
                toAttack = player->toAttack(new Bomb());
                if (toAttack && !toAttack->empty()) {
                    source = toAttack->at(0);
                    target = toAttack->at(1);
                    cout << *player->getName() << " has played a BOMB card" << endl;
                    auto *b = new Bomb(player, source, target);
                    player->issueOrder(b);
                }
                else {
                    cout << *player->getName() << " is unable to play BOMB. They have no territories designated to attack." << endl;
                    cardPlayed = false;
                }
                break;
            case REINFORCEMENT:
                cout << *player->getName() << " has played a REINFORCEMENT card\n";
                toDefend = player->toDefend(new Deploy());
                if (toDefend) {
                    source = toDefend->back();
                    auto *d = new Deploy(player, source, 3);
                    player->setArmies(player->getArmies() + 3);
                    player->issueOrder(d);
                }
                else {
                    cout << *player->getName() << " is unable to play REINFORCEMENT. They have no territories designated to defend." << endl;
                    cardPlayed = false;
                }
                break;
            case BLOCKADE:
                toDefend = player->toDefend(new Blockade());
                if (toDefend) {
                    cout << *player->getName() << " has played a BLOCKADE card\n";
                    source = toDefend->front();
                    auto *b = new Blockade(player, source);
                    player->issueOrder(b);
                }
                else {
                    cardPlayed = false;
                }
                break;
            case AIRLIFT:
                toDefend = player->toDefend(new Airlift());
                if (toDefend) {
                    cout << *player->getName() << " has played a AIRLIFT card\n";
                    target = toDefend->back();
                    source = toDefend->front();
                    int armies;
                    if (dynamic_cast<HumanPlayerStrategy *>(player->getPlayerStrategy())) {
                        cout << "How many armies would you like to airlift from " << *target->getName() << " ?" << endl;
                        cin >> armies;
                    }
                    else {
                        armies = (source->getNumberOfArmies() + 1) /2;
                    }
                    auto *a = new Airlift(player, source, target, armies);
                    player->issueOrder(a);
                }
                else {
                    cout << *player->getName() << " is unable to play AIRLIFT. They have no territories to airlift from." << endl;
                    cardPlayed = false;
                }
                break;
            case DIPLOMACY:
                if (!player->issueOrder(new Negotiate())){
                    cardPlayed = false;
                }
                else {
                    cout << *player->getName() << " has played a DIPLOMACY card\n";
                }
                break;
            default:
                break;
        }
    if (cardPlayed) {
        deck->addCardBackToDeck(this);
        return true;
    }
    else {
        return false;
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
    cardsInDeck = new class Card*[initialDeckSize];
    initialDeck = new class Card[initialDeckSize];
    this->initialize();

    cout << "Deck object were successfully CREATED\n";
}

//Deck Constructor of specific size
Deck::Deck(int deckSize)
{
    initialDeckSize = deckSize;
    nbCardInDeck = deckSize;
    if (nbCardInDeck < 0) {
        cout << "Not a valid deck size; The deck size will be initiated with 55 cards.\n";
        initialDeckSize = 55;
        nbCardInDeck = 55;
    }
    cardsInDeck = new Card*[initialDeckSize];
    initialDeck = new Card[initialDeckSize];

    this->initialize();

//    cout << "Deck object were successfully CREATED\n";
}
//copy constructor
Deck::Deck(const Deck &obj){
    cardsInDeck = new Card*[initialDeckSize];
    initialDeck = new Card[initialDeckSize];

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
Deck& Deck::operator = (const Deck & deck){
    if (this == &deck){
        return *this;
    }
    **cardsInDeck = **deck.cardsInDeck;
    *initialDeck = *deck.initialDeck;
    initialDeckSize = deck.initialDeckSize;
    nbCardInDeck = deck.nbCardInDeck;
    return *this;
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
        class Card c1 = Card();
        initialDeck[i] = c1;
        cardsInDeck[i] = &initialDeck[i];
    }
}

//Get number of card not in a players hand
int Deck::getCurrentSize() const
{
    return nbCardInDeck;
}


//Put cards back in the deck when it's played
void Deck::addCardBackToDeck(Card *card) {
    for (int i = 0 ; i < nbCardInDeck; i++ ){
        if (!cardsInDeck[i]){
            cardsInDeck[i] = card;
            this->nbCardInDeck ++;
            cout << "Card was successfully placed back in the deck. " << endl;
            break;
        }
    }
}

//Draw card from the deck
Card* Deck::draw() {
    Card *pickedCard;
    int n = getCurrentSize();
    while(n > 0 ){
        int temp = rand() % initialDeckSize;
        pickedCard = cardsInDeck[temp];
        if (pickedCard != nullptr) {
            cardsInDeck[temp] = nullptr;
            nbCardInDeck = n - 1;
            cout << "Player just received this NEW CARD: " << *pickedCard;
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
    maxCard = 5;
    cardsInHand = new Card*[maxCard]();
    nbCardsInHand = obj.nbCardsInHand;
    for (int i = 0; i < obj.nbCardsInHand; i++) {
        cardsInHand[i] = obj.cardsInHand[i];
    }
    maxCard = obj.maxCard;
    cout << "Hand object was successfully CREATED\n";
}

//destructor
Hand::~Hand(){
    delete[] cardsInHand;
    cout << "Hand object was successfully DELETED\n";
}

//assignment operator overloading
Hand& Hand::operator = (const Hand & hand){
    if (this == &hand) {
        return *this;
    }
    delete[] cardsInHand;
    cardsInHand = new Card*[maxCard]();
    nbCardsInHand = hand.nbCardsInHand;
    for (int i = 0; i < hand.nbCardsInHand; i++) {
        cardsInHand[i] = hand.cardsInHand[i];
    }
    maxCard = hand.maxCard;
    cout << "Hand object was successfully CREATED\n";
    return *this;
}

// Draw a card from the deck (add a card in hand)
void Hand::drawFromDeck(Deck* deck){
    if (!deck) {
        cout << "DECK IS NULL" << endl;
        return;
    }
    if (nbCardsInHand == maxCard){
        cout << "Hand is full. Player currently has " << nbCardsInHand << " cards.\n";
    }
    else{
        for (int i = 0 ; i < maxCard; i++ ){
            if (cardsInHand[i] == nullptr){
                cardsInHand[i] = deck->draw();
                nbCardsInHand = nbCardsInHand + 1;
                break;
            }
        }
    }
}

//Play a card in the hand and return it in the deck
bool Hand::playRound(Deck* deck, Player* player)
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
            if (cardsInHand[cardChoice - 1]->play(deck, player)){
                for (int i = cardChoice - 1; i < maxCard; i++) {
                    cardsInHand[i] = cardsInHand[i + 1];
                }
                nbCardsInHand--;
                return true;
            }
        }
    }
    return false;
}
void Hand::playCard(Deck *deck, Player *player, int i) {
    int play = nbCardsInHand - i - 1;
    if (play < 0 || play >= nbCardsInHand){
        cout << *player << " doesn't have any cards to play." << endl;
        if (nbCardsInHand == maxCard) {
            cout << *player << " is discarding a " << *cardsInHand[nbCardsInHand -1] << "card.";
            deck->addCardBackToDeck(cardsInHand[nbCardsInHand -1]);
            nbCardsInHand--;
        }
    }
    else {
        if (cardsInHand[play]->play(deck, player)) {
            nbCardsInHand--;
        }
        else {
            playCard(deck, player, ++i);
        }
    }
}


// Print all the cards in hand
std::ostream &operator << (std::ostream &out, const Hand &hand ){
    for( int i = 0 ; i < hand.nbCardsInHand ; i++ ){
        out << "\nCard #" << i+1 << " " << *hand.cardsInHand[i];
    }
    return out;
}




