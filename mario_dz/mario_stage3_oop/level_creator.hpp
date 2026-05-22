#ifndef LEVEL_CREATOR
#define LEVEL_CREATOR

#include "objects.hpp"

class Level_Creator {
    public:
        static void create_level(int level, 
            Brick* &bricks, int &bricks_number, 
            Movable* &movables, int &movables_number
        );

        template <typename T>
        static T *get_new_object(T* &obj_arr, int &obj_number); 
};

#endif