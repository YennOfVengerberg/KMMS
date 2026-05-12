#ifndef FUNCTIONS
#define FUNCTIONS

#include <iostream>
#include <cstdlib>

#include <cmath>
#include <windows.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 25

// struct Object {
//     float x, y;
//     float height, width;
//     float vert_speed;
//     float horiz_speed;
//     bool in_air;
//     char c_type;
// };


 

class Object {
    private:
        float x, y;
        float height, width;
        float vert_speed, horiz_speed;
        bool in_air;
        char object_type;

    public: 
        void init_object(float x_pos, float y_pos, float o_width, float o_height, char obj_type);
        void set_object_pos(float x_pos, float y_pos);

    public:
        void set_air_state(bool state);

        bool in_air_state();
        std::pair<int, int> get_coordinates();
        std::pair<float, float> get_height_width();

        char get_object_type();
        
        void change_vertical_speed(float dy);
        void change_horizontal_speed(float dx);

        void move_horizontal(float dx);
        void move_vertical(float dy);

        void set_object_type(char new_type);

        std::pair<float, float> get_vert_horiz_speeds();
};

class Map {
    private:
        char map[MAP_HEIGHT][MAP_WIDTH + 1] = {};

    public:
        void clear_map();
        void show_map();
        void display_score(int score);
        void put_object_on_map(Object obj);
        void set_cursor(int x, int y);
        bool is_pos_in_map(int x, int y);
}; 

class Game {
    private:
        Map map;
    
        Object memerio;

        Object *bricks = nullptr;
        int bricks_number;

        Object *movables = nullptr;
        int movables_number;

        int score;
        int level = 1;
        int max_level;

    public:
        
};

void create_level(int level, Object* &bricks, int &bricks_number, Object* &movables, 
    int &movables_number, int &score, int &max_level, Object &memerio);

void player_collision(Object* &movables, int &movables_number, int &bricks_number, 
    Object* &bricks, int &score, int &level, int &max_level, Object &memerio); //game logic
void player_died(int level, Object* &bricks, int &bricks_number, 
    Object* &movables, int &movables_number, int &score, int &max_level, Object &memerio);
void vert_move_object(Object *obj, Object* &bricks, Object* &movables, 
    int &bricks_number, int &movables_number, int &score, int &level, int &max_level, Object &memerio);
void horizon_move_object(Object *obj, Object* &bricks, Object* &movables, 
    int &bricks_number, int &movables_number, int &score, int &level, int &max_level, Object &memerio);
void horizontal_move_map(float dx, Object* &bricks, Object* &movables, 
    int bricks_number, int movables_number, Object &memerio);

//void set_object_pos(Object *obj, float x_pos, float y_pos); //

bool is_collision(Object obj1, Object obj2); 
//inits
//void init_object(Object *obj, float x_pos, float y_pos, float o_width, float o_height, char obj_type); //
Object *get_new_object(Object* &obj_arr, int &obj_number);
void delete_obj(Object* &obj_arr, int &obj_number, int i);

#endif