//
// Created by Noah on 2019-09-26.
//

#include "Cards.h"
#include <algorithm>
#include <ctime>

using namespace std;


namespace Cards {

    int Deck::totalSetsTraded = 0;

Card::Card() {
    this->country = new string;
    this->type = new Card::Type;
}

Card::Card(string country, Card::Type type) {
    this->country = new string(country);
    this->type = new Card::Type(type);
}

Card::~Card() {
    delete country;
    delete type;

    country = nullptr;
    type = nullptr;
}

string * Card::get_country() {
    return country;
}

Card::Type Card::get_type() {
    return *type;
}

Card::Card(Card &card) {
    this->country = new string(*card.get_country());
    this->type = new Card::Type(card.get_type());
}

string Card::to_string() {

    switch (*type){
        case INFANTRY:
            return "Card type: infantry, country: " + *get_country();
        case ARTILLERY:
            return "Card type: artillery, country: " + *get_country();
        case CAVALRY:
            return "Card type: cavalry, country: " + *get_country();
    }
    return "";
}

Deck::Deck() {
    cards = new vector<Card *>;
}

Deck::Deck(vector<Card *> &cards) {
    this->cards = new vector<Card *>(cards.size());
    auto deckCardsIterator = this->cards->begin();
    auto passedCardsIterator = cards.begin();
    for (size_t i = 0; i < cards.size(); i++) {
        *deckCardsIterator = new Card(**passedCardsIterator);
        deckCardsIterator++;
        passedCardsIterator++;
    }
}

Deck::~Deck() {
    delete cards;
    cards = nullptr;
    totalSetsTraded = 0;
}


Card Deck::draw() {
    Card card(*(cards->back()));
    cards->pop_back();
    return card;
}

void Deck::shuffleDeck() {
    unsigned long random = 0;
    const auto iter = cards->begin();
    srand (time(NULL));
    for (size_t i = 0; i < cards->size(); i++) {
        random = rand() % cards->size();
        iter_swap(iter + i, iter+random);
    }
}

Deck::Deck(const vector<string>& countries) {
    cards = new vector<Card *>;
    int starting = rand() % 3;
    for (int i = 0; i < countries.size(); i++) {
        Card card(countries.at(i), Card::Type((starting + i) % 3));
        cards->push_back(new Card(card));
    }
}

    int Deck::get_size() {
        return this->cards->size();
    }

Hand::Hand() {
    cards = new vector<Card *>;
}

Hand::~Hand() {
    delete cards;

    cards = nullptr;
}



void Hand::insertCard(Card card) {
    cards->push_back(new Card(card));
}

int Hand::exchange(int cardIndices[]) {
    sort(cardIndices, cardIndices+3);
    cards->erase(cards->begin() + cardIndices[2]);
    cards->erase(cards->begin() + cardIndices[1]);
    cards->erase(cards->begin() + cardIndices[0]);

    int numArmiesToReturn;
    if ( Deck::totalSetsTraded  < 5) {
        numArmiesToReturn = 4 + Deck::totalSetsTraded  * 2;
    } else {
        numArmiesToReturn = 15 + 5 * (Deck::totalSetsTraded  - 5);
    }
    (Deck::totalSetsTraded)++;
    return numArmiesToReturn;
}

bool Hand::sameCardCheck(const int *handIndices) {
    return (handIndices[0] == handIndices[1] || handIndices[0] == handIndices[2] || handIndices[1] == handIndices[2]);
}

bool Hand::cardsValidForExchange(const int *handIndices){
    if (sameCardCheck(handIndices)) {
        return false;
    }
    bool typeFlags[] = {false, false, false};
    for (int i = 0; i < 3; i++) {
        typeFlags[this->cards->at(handIndices[i])->get_type()] = true;
    }
    int count = 0;
    for (bool typeFlag : typeFlags) {
        if (typeFlag) {
            count++;
        }
    }
    return (count == 1 || count == 3);
}

    int Hand::size() {
        return cards->size();
    }

    vector<Card *> * Hand::get_cards() {
        return cards;
    }
}