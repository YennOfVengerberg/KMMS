#include "functions.hpp"
#include "obj_types.hpp"



int main() {
    Map map;
    
    Object memerio;

    Object *bricks = nullptr;
    Object *movables = nullptr;
    int movables_number;
    int bricks_number;

    int score;
    int level = 1;
    int max_level;

    create_level(level, bricks, bricks_number, movables, movables_number, score, max_level, memerio);

    do  {
        map.clear_map();

        if(memerio.in_air_state() == false && GetKeyState(VK_UP) < 0) memerio.change_vertical_speed(-2 * 1.0);
        if(GetKeyState(VK_LEFT) < 0) horizontal_move_map(1, bricks, movables, bricks_number, movables_number, memerio);
        if(GetKeyState(VK_RIGHT) < 0) horizontal_move_map(-1, bricks, movables, bricks_number, movables_number, memerio);

        if(memerio.get_coordinates().second > MAP_HEIGHT) player_died(level, bricks, bricks_number, movables, movables_number, score, max_level, memerio);

        vert_move_object(&memerio, bricks, movables, bricks_number, movables_number, score, level, max_level, memerio);
        player_collision(movables, movables_number, bricks_number, bricks, score, level, max_level, memerio);

        for(int i = 0; i < bricks_number; i++) {
            map.put_object_on_map(bricks[i]);
        }
        for(int i = 0; i < movables_number; i++) {
            vert_move_object(movables + i, bricks, movables, bricks_number, movables_number, score, level, max_level, memerio);
            horizon_move_object(movables + i, bricks, movables, bricks_number, movables_number, score, level, max_level, memerio);
            if(movables[i].get_coordinates().second > MAP_HEIGHT) {
                delete_obj(movables, movables_number, i);
                i--;
                continue;
            }
            map.put_object_on_map(movables[i]);
        }

        map.put_object_on_map(memerio);
        map.display_score(score);


        map.set_cursor(0, 0);
        map.show_map();

        Sleep(10);
    } while(GetKeyState(VK_ESCAPE) >= 0);
    return 0;
    
}