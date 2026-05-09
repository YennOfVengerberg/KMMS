#include "functions.hpp"

TObject memerio;

int main() {

    char map[MAP_HEIGHT][MAP_WIDTH + 1] = {};
    
    TObject *bricks = nullptr;
    TObject *movables = nullptr;
    int movables_number;
    int bricks_number;

    int score;
    int level = 1;
    int max_level;

    create_level(level, bricks, bricks_number, movables, movables_number, score, max_level);

    do  {
        clear_map(map);

        if(memerio.in_air == FALSE && GetKeyState(VK_UP) < 0) memerio.vert_speed = -1.0;
        if(GetKeyState(VK_LEFT) < 0) horizontal_move_map(1, bricks, movables, bricks_number, movables_number);
        if(GetKeyState(VK_RIGHT) < 0) horizontal_move_map(-1, bricks, movables, bricks_number, movables_number);

        if(memerio.y > MAP_HEIGHT) player_died(level, bricks, bricks_number, movables, movables_number, score, max_level);

        vert_move_object(&memerio, bricks, movables, bricks_number, movables_number, score, level, max_level);
        player_collision(movables, movables_number, bricks_number, bricks, score, level, max_level);

        for(int i = 0; i < bricks_number; i++) {
            put_object_on_map(bricks[i], map);
        }
        for(int i = 0; i < movables_number; i++) {
            vert_move_object(movables + i, bricks, movables, bricks_number, movables_number, score, level, max_level);
            horizon_move_object(movables + i, bricks, movables, bricks_number, movables_number, score, level, max_level);
            if(movables[i].y > MAP_HEIGHT) {
                delete_obj(movables, movables_number, i);
                i--;
                continue;
            }
            put_object_on_map(movables[i], map);
        }

        put_object_on_map(memerio, map);
        display_score(score, map);


        set_cursor(0, 0);
        show_map(map);

        Sleep(10);
    } while(GetKeyState(VK_ESCAPE) >= 0);
    return 0;
    
}