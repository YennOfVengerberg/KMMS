#include "functions.hpp"

#define map_width 80
#define map_height 25

int main() {
    char map[map_height][map_width+1];

    TObject memerio;
    TObject *bricks = NULL;
    TObject *movables = NULL;
    int movables_number;
    int bricks_number;
    
    int score;
    int level = 1;
    int max_level;

    create_level(level);


    do  {
        clear_map();

        if(memerio.in_air == FALSE && GetKeyState(VK_UP) < 0) memerio.vert_speed = -1.0;
        if(GetKeyState(VK_LEFT) < 0) horizontal_move_map(1);
        if(GetKeyState(VK_RIGHT) < 0) horizontal_move_map(-1);

        if(memerio.y > map_height) player_died();

        vert_move_object(&memerio);
        player_collision();

        for(int i = 0; i < bricks_number; i++) {
            put_object_on_map(brick[i]);
        }
        for(int i = 0; i < movables_number; i++) {
            vert_move_object(movables + i);
            horizon_move_object(movables + i);
            if(movables[i].y > map_height) {
                delete_movable(i);
                i--;
                continue;
            }
            put_object_on_map(movables[i]);
        }

        put_object_on_map(memerio);
        display_score();


        set_cursor(0, 0);
        show_map();

        Sleep(10);
    } while(GetKeyState(VK_ESCAPE) >= 0);
    return 0;
    
}