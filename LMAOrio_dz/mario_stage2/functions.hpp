#ifndef FUNCTIONS
#define FUNCTIONS

#include <iostream>
#include <cstdlib>

#include <cmath>
#include <windows.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 25

struct TObject {
    float x, y;
    float height, width;
    float vert_speed;
    float horiz_speed;
    bool in_air;
    char c_type;
};


void clear_map(); //displays
void show_map();
void display_score();
void set_cursor(int x, int y);
void create_level(int level);

void player_collision(); //game logic
void player_died();
void vert_move_object(TObject *obj);
void horizon_move_object(TObject *obj);
void horizontal_move_map(float dx);
void put_object_on_map(TObject obj);
void set_object_pos(TObject *obj, float x_pos, float y_pos);
bool is_pos_in_map(int x, int y);
bool is_collision(TObject obj1, TObject obj2);
//inits
void init_object(TObject *obj, float x_pos, float y_pos, float o_width, float o_height, char obj_type);
TObject *get_new_brick();
TObject *get_new_movable();
void delete_movable(int i);

#endif