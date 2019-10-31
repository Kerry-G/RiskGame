//TESTS INCLUDES
#include "Map/MapDriver.h"
#include "Dice/DiceDriver.h"
#include "MapLoader/MapLoaderDriver.h"
#include "GameEngine/GameEngineDriver.h"
#include "Cards/CardsDriver.h"
#include "Player/PlayerDriver.h"
#include "Terminal/Terminal.h"
//RUN INCLUDES
#include "GameEngine/GameEngine.h"

using namespace std;

int main() {

    Terminal::print("Domination Game - Team 12 - COMP 345");

    bool test = false; // Maybe add a way to read sys args?

    Terminal::debug_mode_on();
    if (test) {
        Terminal::test_mode_on();
        Terminal::run_test("MapLoader", MapLoader::Driver::run);
        Terminal::run_test("Map", Board::Driver::run);
        Terminal::run_test("Dice", Dice::Driver::run);
        Terminal::run_test("Cards", Cards::Driver::run);
        Terminal::run_test("Player", Player::Driver::run);
        Terminal::run_test("GameEngine", GameEngine::Driver::run);
    }

    //    GameEngine::GameEngine::instance()->start_test(0,6);
//
    Terminal::test_mode_on();
    GameEngine::GameEngine::instance()->start_test(0,2);
    GameEngine::GameEngine::instance()->startup_phase();
//    GameEngine::GameEngine::instance()->game_loop();

    return 0;
}