//
// Created by Lynn Tedje Anna Meindertsma on 08 Apr 2024.
//
#ifndef YAHTZEE_GAME_HPP
#define YAHTZEE_GAME_HPP

#include <cstdint>
#include "dice.hpp"
#include "player.hpp"

class Game {
public:
    //Constructor
    Game();

    //Methode to start the game
    void start_game();

    //Methode to choose game category
    uint8_t game_category();

    //Methode to proceed to the next player's turn
    void next_roll();

    //Methode to proceed to the next player's round
    void next_round();

    //Methode to determine the winner and end the game
    void end_game();

private:
    Dice dices[5];
    Player player;
    uint32_t num_players = 0;
    uint32_t start;
    // Dynamically allocate an array of Player objects
    Player* players = new Player[num_players];
};

#endif //YAHTZEE_GAME_HPP
