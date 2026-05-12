#ifndef MAP_AND_DISPLAYS
#define MAP_AND_DISPLAYS

#define MAP_WIDTH 80
#define MAP_HEIGHT 25

#include <cmath>
#include <windows.h>

#include "objects.hpp"

class Map {
    private:
        char map[MAP_HEIGHT][MAP_WIDTH + 1] = {};

    public:
        void clear_map();
        void show_map();

        void display_score(int score);
        
        void set_cursor(int x, int y);

        void put_object_on_map(Object obj);
        bool is_pos_in_map(int x, int y);
}; 

#endif