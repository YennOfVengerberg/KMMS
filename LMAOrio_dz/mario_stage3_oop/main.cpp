#include "game_logic.hpp"
#include "map_and_displays.hpp"
#include "objects.hpp"

int main() {
    Game game_state;

    game_state.create_level();
    game_state.run_game_loop();
    // Map map;
    // Movable mario;
    // do  {
    //     map.clear_map();

    //     if(mario.in_air_state() == false && GetKeyState(VK_UP) < 0) mario.set_vert_speed(-1.0);
    //     if(GetKeyState(VK_LEFT) < 0) game_state.horizontal_move_map(1);
    //     if(GetKeyState(VK_RIGHT) < 0) game_state.horizontal_move_map(-1);

    //     if(mario.get_obj_dimensions().y > MAP_HEIGHT) game_state.player_died();

    //     game_state.vert_move_object(&mario);
    //     game_state.player_collision();

    //     for(int i = 0; i < bricks_number; i++) {
    //         map.put_object_on_map(bricks[i]);
    //     }
    //     for(int i = 0; i < movables_number; i++) {
    //         game_state.vert_move_object(movables + i);
    //         game_state.horizon_move_object(movables + i);
    //         if(movables[i].get_obj_dimensions().y > MAP_HEIGHT) {
    //             game_state.delete_obj(movables, movables_number, i);
    //             i--;
    //             continue;
    //         }
    //         map.put_object_on_map(movables[i]);
    //     }

    //     map.put_object_on_map(mario);
    //     map.display_score(score);


    //     map.set_cursor(0, 0);
    //     map.show_map();

    //     Sleep(10);
    // } while(GetKeyState(VK_ESCAPE) >= 0);
    return 0;
    
}