//
// Created by Lynn Tedje Anna Meindertsma on 08 Apr 2024.
//
#include<iostream>
#include<cstdlib>
#include <string>
#include <algorithm>

#include "game.hpp"

using namespace std;

Game::Game() {}
//todo: does not go 5 rounds
uint8_t Game::game_category() {
    //normal game
    if (start == 1){
        return 13;
    }
    //short game
    if (start == 2){
        return 5;
    } else { return 0; }
}

void Game::start_game() {
    printf("Do you want to play a game? \n");
    printf("answer 0 for NO, 1 for Standard and 2 for Short game mode. \n");
    scanf("%d", &start);
    if (start == 1) {
        game_category();
        printf("Enter the number of players: \n");
        scanf("%d", &num_players);

        // Initialize each player
        for (int i = 0; i < num_players; ++i) {
            players[i].initialize();
        }
        //loop through until every player had had its turn
        for (int i = 0; i < num_players; ++i) {
            std::cout << "Your turn: " << players[i].get_name() << "!\n";
            printf("%s", "Your throw is: ");
            //dice roll
            for ( i = 0; i < 5; ++i) {
                dices[i].roll();
            }
            //print dice value
            for ( i = 0; i < 5; ++i) {
                printf("%d ", dices[i].get_value());
            }
            printf("\n");
            next_roll();
            players[i].set_score(dices);
        }
    }
    if (start == 2 ){
        game_category();
        printf("Enter the number of players: \n");
        scanf("%d", &num_players);

        // Initialize each player
        for (int i = 0; i < num_players; ++i) {
            players[i].initialize();
        }
        //loop through until every player had had its turn
        for (int i = 0; i < num_players; ++i) {
            std::cout << "Your turn: " << players[i].get_name() << "!\n";
            printf("%s", "Your throw is: ");
            //dice roll
            for (int j = 0; j < 5; ++j) {
                dices[j].roll();
            }
            //print dice value
            for (int j = 0; j < 5; ++j) {
                printf("%d ", dices[j].get_value());
            }
            printf("\n");
            next_roll();
            players[i].set_score(dices);
        }
    }else {
        printf("%s", " :( ");
    }
}
void Game::next_roll() {
    uint32_t reroll;
    //You can reroll only two times per round
    for (int i = 0; i < 2; ++i) {
        printf("Do you want to reroll any of the dice? (Enter the index of the dice you want to reroll) \n");
        do {
            // get answer from user
            scanf("%d", &reroll);
            if (reroll != 0) {
                dices[reroll - 1].roll();
            }
        } while (reroll != 0);
        printf("%s", "Your throw is: ");
        //print dice value
        for (int j = 0; j < 5; ++j) {
            printf("%d ", dices[j].get_value());
        }
        printf("\n");
    }
    //todo:bonus yahtzee bug
}

void Game::next_round() {
    for (int i = 0; i < num_players; ++i) {
        printf("\n%s\n", "Next round begins");
        std::cout << "Your turn: " << players[i].get_name() << "!\n";
        printf("%s", "Your throw is: ");
        //dice roll
        for (int j = 0; j < 5; ++j) {
            dices[j].roll();
        }
        //print dice value
        for (int j = 0; j < 5; ++j) {
            printf("%d ", dices[j].get_value());
        }
        printf("\n");
        next_roll();
        players[i].set_score(dices);
    }
}

void Game::end_game() {
    //todo: who wins calc

    for (int i = 0; i < num_players; ++i) {
        printf("\n");
        std::cout << players[i].get_name() << ", your end score is: " << "\n";
        printf("%d\n", players[i].get_total_score());
    }

    // Sort players based on their total score (from highest to lowest)
    for (int i = 0; i < num_players - 1; ++i) {
        for (int j = i + 1; j < num_players; ++j) {
            if (players[i].get_total_score() < players[j].get_total_score()) {
                std::swap(players[i], players[j]);
            }
        }
    }
    // Assign rankings based on the sorted order
    for (int i = 0; i < num_players; ++i) {
        players[i].set_ranking(i + 1);
    }

    // Print each player's ranking and score
    for (int i = 0; i < num_players; ++i) {
        std::cout << players[i].get_name() << "\n";
        printf("Your ranking is: %d\n", players[i].get_ranking());
        printf("Your total score is: %d\n", players[i].get_total_score());
    }
}