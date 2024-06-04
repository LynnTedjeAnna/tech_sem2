//
// Created by Lynn Tedje Anna Meindertsma on 08 Apr 2024.
//
#ifndef YAHTZEE_SCORECARD_HPP
#define YAHTZEE_SCORECARD_HPP

#include "dice.hpp"

/*
 #define BONUS_SCORE 63
 #define BONUS_POINTS 35
 #define POINTS_FULL_HOUSE 25
 #define POINTS_SMALL_STRAIGHT 30
 #define POINTS_LARGE_STRAIGHT 40
 #define POINTS_YAHTZEE 50
 #define BONUS_POINTS_YAHTZEE 100
*/

class Scorecard {
public:
    //Constructor
    Scorecard();

    //Methode to print scorecard
    void print_score();

    //Methode to set scores for different categories
    void set_score(const Dice dices[5]);

    //Methode to check value for the scores
    bool check_score();

    // Method to check for 3 or 4 of the same values in the dice rolls
    bool check_duplicates(const Dice dices[5]);

    //Methode to check ascending values in teh dice rolls
    bool check_ascending(const Dice dices[5]);

    //Methode to calculate the total score for a player
    uint16_t calc_total_score();

private:
    static const uint8_t BONUS_SCORE = 63;              //todo: define
    static const uint8_t BONUS_POINTS = 35;             //todo: define
    static const uint8_t POINTS_FULL_HOUSE = 25;        //todo: define
    static const uint8_t POINTS_SMALL_STRAIGHT = 30;    //todo: define
    static const uint8_t POINTS_LARGE_STRAIGHT = 40;      //todo: define
    static const uint8_t POINTS_YAHTZEE = 50;           //todo: define
    static const uint8_t POINTS_BONUS_YAHTZEE = 100;    //todo: define
    uint16_t total_score = 0;
    uint8_t part1_scorecard[6];
    uint8_t three_kind = 0;
    uint8_t four_kind = 0;
    uint8_t full_house = 0;
    uint8_t small_straight = 0;
    uint8_t large_straight = 0;
    uint8_t yahtzee = 0;
    uint8_t bonus_yahtzee = 0;
    uint8_t chance = 0;
    uint32_t select;
};
#endif //YAHTZEE_SCORECARD_HPP