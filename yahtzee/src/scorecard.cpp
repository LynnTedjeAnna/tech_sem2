//
// Created by Lynn Tedje Anna Meindertsma on 08 Apr 2024.
//
#include <cstdio>
#include <algorithm>

#include "scorecard.hpp"

Scorecard::Scorecard() {
    for (int i = 0; i < 6; ++i) {
        part1_scorecard[i] = 0;
    }
}
//todo: bonus yahtzee u dont lose a turn || u gain a turn

void Scorecard::print_score() {
    total_score = 0;
    for (uint8_t i = 0; i < 6; ++i) {
        total_score = total_score +part1_scorecard[i];
    }
    printf("\nScores:\n");
    printf("1. Ones: %d\n", part1_scorecard[0]);
    printf("2. Twos: %d\n", part1_scorecard[1]);
    printf("3. Threes: %d\n", part1_scorecard[2]);
    printf("4. Fours: %d\n", part1_scorecard[3]);
    printf("5. Fives: %d\n", part1_scorecard[4]);
    printf("6. Sixes: %d\n", part1_scorecard[5]);
    printf("----------------------------");
    printf("total above score: %d\n", total_score);
    printf("7. Three of a Kind: %d\n", three_kind);
    printf("8. Four of a Kind: %d\n", four_kind);
    printf("9. Full House: %d\n", full_house);
    printf("10. Small Straight: %d\n", small_straight);
    printf("11. Large Straight: %d\n", large_straight);
    printf("12. Yahtzee: %d\n", yahtzee);
    printf("13. Chance: %d\n", chance);
    printf("\n");
    printf("14. Bonus yahtzee: %d\n", bonus_yahtzee);
    printf("\n");
}
bool Scorecard::check_score(){
    if (select < 6 && part1_scorecard[select - 1] != 0) return false;
    if (select == 7 && three_kind != 0) return false;
    if (select == 8 && four_kind != 0) return false;
    if (select == 9 && full_house != 0) return false;
    if (select == 10 && small_straight != 0) return false;
    if (select == 11 && large_straight != 0) return false;
    if (select == 12 && yahtzee != 0) return false;
    if (select == 13 && bonus_yahtzee != 0) return false;
    if (select == 14 && chance != 0) return false;
    return true;
}
bool Scorecard::check_duplicates(const Dice dices[5]) {
    //todo: pass over the duplicates not dices themself

    // Extract the values from the Dice objects and store them in an array of int
    uint8_t dice_values[5];
    for (int i = 0; i < 5; ++i) {
        dice_values[i] = dices[i].get_value();
    }
    // Sort the dice values
    std::sort(dice_values, dice_values + 5);
    uint8_t count = 1;
    // Iterate through sorted dice values to find duplicates
    for (int i = 0; i < 4; ++i) {
        // Check if the current element is the same as the next element
        //todo: when full house count is 4 rn PROBLEM
        if (dice_values[i] == dice_values[i + 1]) {
            count++;
        }
    }
    if ((select == 7) && (count > 2)) { return true; }
    if (select == 8 && count > 3) { return true; }
    if (select == 9 && count == 4) { return true; }
    if (select == 12 && count == 5) { return true; }
    //bonus yahtzee can only be used after the first yahtzee
    if (select == 14 && yahtzee == 0) { return false; }
    if (select == 14 && count == 5) { return true; }
    else return false;
}
bool Scorecard::check_ascending(const Dice dices[5]) {

    // Extract the values from the Dice objects and store them in an array of int
    uint8_t dice_values[5];
    for (int i = 0; i < 5; ++i) {
        dice_values[i] = dices[i].get_value();
    }
    // Sort the dice values
    std::sort(dice_values, dice_values + 5);
    uint8_t count = 1;
    // Iterate through sorted dice values to find duplicates
    for (int i = 0; i < 4; ++i) {
        // Check if the current element is the one lower as the next element
        if (dice_values[i] < dice_values[i + 1]) {
            count++;
        }
    }
    //Count under the value 4 return false

    if (select == 10 && count > 3) { return true; }
    if (select == 11 && count > 4) { return true; }
    else return false;
}
void Scorecard::set_score(const Dice dices[5]) {
    print_score();
    //check if input is correct and only break out when correct
    do {
        printf("Choose what to fill in: \nselect 1-14 \n");
        scanf("%d", &select);
    } while (!check_score());
    while (!check_duplicates(dices) && ((select == 7) || (select == 8) || (select == 9) || (select == 12) || (select == 14))){
        printf("Choose what to fill in: \nselect 1-14 \n");
        scanf("%d", &select);
    }
    while (!check_ascending(dices) && ((select == 10) || (select == 11))){
        printf("Choose what to fill in: \nselect 1-14 \n");
        scanf("%d", &select);
    }
    if (select <= 6){
        uint8_t add_up_dices = 0;
        for (int i = 0; i < 5; ++i) {
            if (dices[i].get_value() == select) {
                add_up_dices += dices[i].get_value();
            }
        }
        part1_scorecard[select - 1] = add_up_dices;
    }

    switch (select) {
        //Three of a kind
        case 7: {
            for (int i = 0; i < 5; ++i) {
                three_kind += dices[i].get_value();
            }
            break;
        }
        //Four of a kind
        case 8: {
            for (int i = 0; i < 5; ++i) {
                four_kind += dices[i].get_value();
            }
            break;
        }
        //Full house
        case 9: {
            full_house = POINTS_FULL_HOUSE;
            break;
        }
        //Small straight
        case 10: {
            small_straight = POINTS_SMALL_STRAIGHT;
            break;
        }
        //Large straight
        case 11: {
            large_straight = POINTS_LARGE_STRAIGHT;
            break;
        }
        //Yahtzee
        case 12: {
            yahtzee = POINTS_YAHTZEE;
            break;
        }
        //chance
        case 13: {
            for (int i = 0; i < 5; ++i) {
                chance += dices[i].get_value();
            }
            break;
        }
        //Bonus yahtzee
        case 14:{
            bonus_yahtzee = POINTS_BONUS_YAHTZEE;

            break;
        }
        default:{
            break;
        }
    }
    print_score();
}
uint16_t Scorecard::calc_total_score() {
    total_score = 0;

    for (uint8_t i = 0; i < 6; ++i) {
        total_score = total_score +part1_scorecard[i];
    }
    if (total_score >= BONUS_SCORE){
        total_score += BONUS_POINTS;
    }
    total_score += three_kind;
    total_score += four_kind;
    total_score += full_house;
    total_score += small_straight;
    total_score += large_straight;
    total_score += yahtzee;
    total_score += bonus_yahtzee;
    total_score += chance;

    return  total_score;
}