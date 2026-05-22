#ifndef GAME_LOGIC
#define GAME_LOGIC

#include "map_and_displays.hpp"
#include "objects.hpp"

// struct game_info {

//     int score;
//     int level_score;
//     int current_level;
//     int max_level;
// };

class Game {
    private:
        //Map map;
    
        Mario mario;

        Brick *bricks = nullptr;
        int bricks_number;

        Movable *movables = nullptr;
        int movables_number;

        int score;
        int level_score;

        int current_level = 1;
        int max_level = 4;

    public:
        Game(Mario *mario, Brick *bricks, int bricks_number, Movable *movables, int movables_number);
        template <typename T>
        T *get_new_object(T* &obj_arr, int &obj_number);

        template <typename T>
        void delete_obj(T* &obj_arr, int &obj_number, int i);


        bool is_collision(Object obj1, Object obj2);
        void player_collision();

        void horizon_move_object(Movable *obj);
        void vert_move_object(Movable *obj);
        void horizontal_move_map(float dx);

        //void create_level();
        
        //void player_died();

        //void run_game_loop();

        int get_score() const;

};

#endif