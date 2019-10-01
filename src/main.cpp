#include <iostream>
#include "Map/MapDriver.h"
#include "DiceRoller/DiceDriver.h"

using namespace std;

int main() {
    cout << "Domination Game - Team 12 - COMP 345" << endl;

    Map::Driver::run();
    DiceDriver::run();

    return 0;
}