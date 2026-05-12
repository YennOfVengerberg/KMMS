#ifndef OBJECTS
#define OBJECTS

#include <iostream>

class Object {
    private:
        float x, y;
        float height, width;
        float vert_speed, horiz_speed;
        bool in_air;
        char object_type;

    public: 
        void set_object_pos(float x_pos, float y_pos);
        void init_object(float x_pos, float y_pos, float o_width, float o_height, char obj_type);
    
    public:
        bool in_air_state();
        
        char get_object_type();

        std::pair<float, float> get_coordinates();
        std::pair<float, float> get_height_width();
        std::pair<float, float> get_vert_horiz_speeds();

        void change_horizontal_speed(float dx);
        void change_vertical_speed(float dy);

        void move_horizontal(float dx);
        void move_vertical(float dy);
        
        void set_air_state(bool state);
        void set_object_type(char new_type);
        void set_horiz_speed(float vx);
        void set_vert_speed(float vy);      
};
#endif