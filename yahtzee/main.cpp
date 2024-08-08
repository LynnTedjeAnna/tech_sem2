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
}