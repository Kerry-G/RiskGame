#pragma once

#include <vector>
#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../Dice/Dice.h"

using namespace std;
using namespace Board;

namespace Player {

    // This is not used, but may be used later
    enum player_color {
        RED=0, BLUE=1, GREEN=2, BLACK=3, GRAY=4, WHITE=5
    };

    class Player {
    private:
        vector<Country *> *countries;
        void fortify();
        //void reinforce();
        bool attack();
        bool is_able_to_attack();
        player_color color;
        static int player_count;
        // The variables below are used for testing
        int armies_assigned;
    public:
        // TODO: These need to be private
        Dice::Dice *dice;
        Cards::Hand *hand;

        Player();
        virtual ~Player();
        /**
         * Take control of a country and handle logic for making sure the player is the only
         * one that has control.
         */
        void gain_control(Country* country);
        static void reset_player_count();

        /**
         * Take control of multiple country and handle logic for making sure the player is the only
         * one that has control. Used for testing mostly.
         */
        void gain_control(vector<Country *> f_countries);

        /**
         * Get a copy of the current list of country pointers
         * @return
         */
        vector<Country *> get_countries();

        vector<Country *> get_countries_attack_source();

        bool is_player_dead();
        string get_color();
        void turn();

        int battle_and_get_last_roll_amount(Country *source, Country *target) const;

        int get_attacker_amount_of_dice(Country *source) const;
        void reinforce();
        vector<string> player_to_string();
        void set_armies_assigned(int a);
        //The methods below are used for testing
        int get_armies_assigned();
    };
}