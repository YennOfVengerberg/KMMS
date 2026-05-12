#include "game_logic.hpp"
#include "map_and_displays.hpp"
#include "objects.hpp"

int main() {
    Game game;
    game.create_level();

    game.run_game_loop();
    return 0;
    
}