#include <iostream>
#include <string>
#include "player.hpp"

Player::Player() {}

void Player::initialize() {
    //todo: change to printf format
    std::cout << "Hello Player, choose your name: \n";
    std::cin >> name;
    std::cout << "Welcome, " << name << "!\n";
    scorecard = Scorecard();
}

void Player::set_score(const Dice dices[5]) {
    scorecard.set_score(dices);
}

std::string Player::get_name() {
    return name;
}

uint16_t Player::get_total_score() {
    total_score = scorecard.calc_total_score();
    return total_score;
}

uint8_t Player::rounds() {
    return 0;
}

void Player::set_ranking(uint8_t rank) {
    ranking_place = rank;
}

uint8_t Player::get_ranking() {
    return ranking_place;
}
