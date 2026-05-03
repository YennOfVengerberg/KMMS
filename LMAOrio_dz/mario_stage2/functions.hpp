#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <cstdlib>

#include <math.h>
#include <windows.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 25

struct TObject {
    float x, y;
    float height, width;
    float vert_speed;
    float horiz_speed;
    BOOL in_air;
    char c_type;
};


void clear_map();

void show_map();

void set_object_pos(TObject *obj, float x_pos, float y_pos);

void init_object(TObject *obj, float x_pos, float y_pos, float o_width, float o_height, char obj_type);

void player_died() ;

TObject *get_new_brick() ;

TObject *get_new_movable() ;

void vert_move_object(TObject *obj) ;

void display_score();

void create_level(int level);

void delete_movable(int i);

void player_collision();

void horizon_move_object(TObject *obj);

BOOL is_pos_in_map(int x, int y);

void put_object_on_map(TObject obj);

void set_cursor(int x, int y);

void horizontal_move_map(float dx);

BOOL is_collision(TObject obj1, TObject obj2);

#endif