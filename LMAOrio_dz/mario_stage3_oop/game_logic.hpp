#ifndef FUNCTIONS
#define FUNCTIONS

#include "map_and_displays.hpp"
#include "objects.hpp"

class Game {
    private:
        Map map;
    
        Object memerio;

        Object *bricks = nullptr;
        int bricks_number;

        Object *movables = nullptr;
        int movables_number;

        int score;
        int current_level = 1;
        int max_level = 4;

    public:
        Object *get_new_object(Object* &obj_arr, int &obj_number);
        void delete_obj(Object* &obj_arr, int &obj_number, int i);

        bool is_collision(Object obj1, Object obj2);
        void player_collision();

        void horizon_move_object(Object *obj);
        void vert_move_object(Object *obj);
        void horizontal_move_map(float dx);

        void create_level();
        
        void player_died();

        void run_game_loop();

};


//inits


#endif