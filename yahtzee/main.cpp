#include <cstdint>
#include <string>

#include "game.hpp"

// Create instances of the classes
Game game;

//Main loop
int main(){

    // Providing a seed value
    srand((unsigned) time(NULL));

    game.start_game();
    //game has max number of rounds
    for (uint8_t i = 0; i < game.game_category(); ++i) {
        game.next_round();
    }

    game.end_game();
}