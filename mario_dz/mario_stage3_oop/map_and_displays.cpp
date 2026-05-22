#include "map_and_displays.hpp"

void Map::clear_map() {
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {   
            map[j][i] = ' ';
        }
        map[j][MAP_WIDTH] = '\0';
    }
}

void Map::show_map() {
    for (int j = 0; j < MAP_HEIGHT; j++) {
        std::cout << map[j];
    }
}
// ----------------

void Map::display_score(int score) {
    char c[30];
    sprintf(c, "SCORE: %d", score);
    int len = strlen(c);
    for(int i = 0; i < len; i++) {
        map[1][i+5] = c[i];
    }
}
// -----------------

void Map::set_cursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// -----------------

void Map::put_object_on_map(Object obj) {
    obj_dimensions obj_dims = obj.get_obj_dimensions();

    int ix = static_cast<int>(round(obj_dims.x));
    int iy = static_cast<int>(round(obj_dims.y));
    int i_width = static_cast<int>(round(obj_dims.width));
    int i_height = static_cast<int>(round(obj_dims.height));

    for(int i = ix; i < (ix + i_width); i++) 
        for(int j = iy; j < (iy + i_height); j++)
            if(is_pos_in_map(i, j))
                map[j][i] = obj.get_object_type();
}

bool Map::is_pos_in_map(int x, int y) {
    return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
}