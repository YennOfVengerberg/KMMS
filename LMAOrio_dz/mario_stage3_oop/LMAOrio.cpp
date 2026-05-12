#include "functions.hpp"
#include "obj_types.hpp"

int main() {
    Game game;
    game.create_level();

    game.run_game_loop();
    return 0;
    
}