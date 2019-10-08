//
//  Dice.hpp
//  DiceRoller
//
//  Created by Francesco Benzi on 2019-09-20.
//

#ifndef Dice_hpp
#define Dice_hpp

#pragma once
#include <vector>
#include <stdio.h>

class Dice
{
    
public:
    
    Dice();
    
    /*
     * roll() rolls one to three dice, registers the new %
     * and returns a sorted container which holds the
     * values of the dice.
     */
    std::vector<int> roll(int numDice);
    
    /*
     * printRollPercentageArray() is a function that prints the current
     * rolling % for all dice values (from 1 to 6).
     */
    
    void printRollPercentageArray();
    
    /*
     * getRollPercentage() is a function that gathers the %
     * value for a specific dice value and returns it as a double.
     */
    
    double getRollPercentage(int roll);
    
    /*
     * getTotalRolls() is a function that returns the total number
     * of dice that has been rolled
     */
    int getTotalRolls();

    ~Dice();

private:
    
    //Pointer Variables
    int *totalRolls;
    double *rollPercentageArray; //stores a value for each dice face [6]

    //Methods
    void initRollPercentArray();
    void addToRollPercentArray(int val);
    
    
};

#endif /* Dice_hpp */
