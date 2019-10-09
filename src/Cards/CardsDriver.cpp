//
// Created by NohaHorowitz on 10/4/2019.
//

#include <vector>
#include <cassert>
#include <iostream>
#include "Cards.h"

namespace Cards {
    namespace Driver {

        bool testDeck() {
            // The Decks were created whit the default constructor here and assigned a new one later.

            vector<Card> cardsBefore, cardsAfter1, cardsAfter2, cardsAfter3;
            Card::Type type;
            const int NUMBER_OF_CARDS = 43;
            string countries[NUMBER_OF_CARDS];


            // Not using default constructor since it was empty


            for (int i = 0; i < NUMBER_OF_CARDS; i++) {
                countries[i] = "Stub name" + to_string(i);
            }

            // Now calling the correct constructor right away.
            Deck deck1(countries, NUMBER_OF_CARDS);
            deck1.shuffleDeck();

            // confirm equal amount of types in deck
            int typeCounter[] = {0, 0, 0};
            for (int i = 0; i < NUMBER_OF_CARDS; i++) {
                Card card(deck1.draw());

                typeCounter[card.getType()]++;
            }

            assert(abs(typeCounter[0] - typeCounter[1]) < 2 && abs(typeCounter[0] - typeCounter[2]) < 2 && abs(typeCounter[1] - typeCounter[2]) < 2 );

            // Assert deck is shuffled randomly, and all three decks are not the same order.
            return true;    // Func needed to return
        }


        bool testHand () {

            int expectedArmiesReturned[] = {4, 6, 8, 10, 12, 15, 20, 25, 30};
            Hand hand;
            const int DECK_SIZE = 42;
            auto cards = vector<Card *>(DECK_SIZE);
            // fill hand with 30
            for (int i = 0; i<DECK_SIZE; i++) {
                 cards.at(i) = new Card("Stub name " + to_string(i), Card::Type(i%3));
            }

            Deck deck(cards);

            // pre-select hand indices to exchange
            int exchangeIndices[] = {2, 1, 0};
            int i = 0;
            while (i < 9) {
                // add three cards to hand
                hand.insertCard(deck.draw());
                hand.insertCard(deck.draw());
                hand.insertCard(deck.draw());

                // assert exchange of pre-selected indices resulted in the expected number of armies returned.
                assert(hand.exchange(exchangeIndices) == expectedArmiesReturned[i]);
                i++;
            }

            return true; // Func needed to return
        }

        bool run() {
            cout << "[TEST] -----" << endl;
            cout << "[TEST] - Running Cards component tests." << endl;

            testDeck();
            testHand();

            cout << "[TEST] - End of Cards component testing." << endl;
            cout << "[TEST] -----" << endl;
            return true;
        }

    }


}
