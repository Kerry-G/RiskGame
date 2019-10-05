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
            string countries[42];


            // Not using default constructor since it was empty


            for (int i = 0; i < 42; i++) {
                countries[i] = "Stub name" + to_string(i);
            }

            // Now calling the correct constructor right away.
            Deck deck1(countries, 42);

            // confirm equal amount of types in deck
            int typeCounter[] = {0, 0, 0};
            for (int i = 0; i < 42; i++) {
                // Card card(deck1.draw());
                // cout << card.getType() << endl;


                // I made "cards" public for testing and explanation purposes (put it back to private after)
                // But.. Here I get int values that are randomly not 0,1 or 2 (Card types)
                // And get_country does a seg. fault.
                // This means that your pointers are not pointing at the correct location
                // (See Deck Constructor for explanation)
                cout << deck1.cards->at(i).getType() << endl;


//                typeCounter[card.getType()]++;
            }

            assert(typeCounter[0] == typeCounter[1] && typeCounter[0] == typeCounter[2]);

            // confirm that deck two and three are randomized.
//            deck1 = Deck(cardsBefore);
//            deck2 = Deck(cardsBefore);
//            deck2.shuffleDeck();
//            deck3 = Deck(cardsBefore);
//            deck3.shuffleDeck();
//
//            int typeCounter[] = {0, 0, 0};
//            for (int i = 0; i < 42; i++) {
//                card = deck1.draw();
//            }



            // Assert deck is shuffled randomly, and all three decks are not the same order.
            return true;    // Func needed to return
        }


        bool testHand () {
//            Card infantryCard = Card("Stub name", Card::Type(0));
//            Card artilleryCard = Card("Stub name", Card::Type(1));
//            Card cavalryCard = Card("Stub name", Card::Type(2));
            Hand hand;
            // fill hand with 30
            for (int i = 0; i<15; i++) {
                hand.insertCard(Card("Stub name", Card::Type(0)));
            }

            int exchangeIndices[] = {0, 1, 2};
            assert(hand.exchange(exchangeIndices) == 2);    // exchange 1
            assert(hand.exchange(exchangeIndices) == 5);    // exchange 2
            assert(hand.exchange(exchangeIndices) == 8);    // exchange 3
            assert(hand.exchange(exchangeIndices) == 11);   // exchange 4
            assert(hand.exchange(exchangeIndices) == 14);   // exchange 5
            assert(hand.exchange(exchangeIndices) == 17);   // exchange 6
            assert(hand.exchange(exchangeIndices) == 20);   // exchange 7
            assert(hand.exchange(exchangeIndices) == 25);   // exchange 8
            assert(hand.exchange(exchangeIndices) == 30);   // exchange 9

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
