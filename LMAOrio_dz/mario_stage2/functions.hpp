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


void clear_map(char map[MAP_HEIGHT][MAP_WIDTH + 1]); //displays
void show_map(char map[MAP_HEIGHT][MAP_WIDTH + 1]);
void display_score(int score, char map[MAP_HEIGHT][MAP_WIDTH + 1]);
void set_cursor(int x, int y);
void create_level(int level, TObject* &bricks, int &bricks_number, TObject* &movables, int &movables_number);

void player_collision(TObject* &movables, int &movables_number, int &bricks_number, TObject* &bricks); //game logic
void player_died(int level, TObject* &bricks, int &bricks_number, TObject* &movables, int &movables_number);
void vert_move_object(TObject *obj, TObject* &bricks, TObject* &movables, int &bricks_number, int &movables_number);
void horizon_move_object(TObject *obj, TObject* &bricks, TObject* &movables, int &bricks_number, int &movables_number);
void horizontal_move_map(float dx, TObject* &bricks, TObject* &movables, int bricks_number, int movables_number);
void put_object_on_map(TObject obj, char map[MAP_HEIGHT][MAP_WIDTH + 1]);
void set_object_pos(TObject *obj, float x_pos, float y_pos);
bool is_pos_in_map(int x, int y);
bool is_collision(TObject obj1, TObject obj2);
//inits
void init_object(TObject *obj, float x_pos, float y_pos, float o_width, float o_height, char obj_type);
TObject *get_new_object(TObject* &obj_arr, int &obj_number);
void delete_obj(TObject* &obj_arr, int &obj_number, int i);

#endif