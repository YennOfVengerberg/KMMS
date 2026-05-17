#ifndef OBJECTS
#define OBJECTS

#include <iostream>

struct obj_dimensions {
    float x, y;
    float height, width;
}; 

struct obj_speeds {
    float vert_speed, horiz_speed;
};

class Object {
    protected:
        obj_dimensions object_dimensions;
        char object_type;

    public: 
        void set_object_pos(float x_pos, float y_pos);
        void init_object(float x_pos, float y_pos, float o_width, float o_height, char obj_type);
    
    public:
        char get_object_type() const;

        obj_dimensions get_obj_dimensions() const;

        void move_horizontal(float dx);
        void move_vertical(float dy);
};

class Brick : public Object {
    public: 
        void set_object_type(char new_type);
};

class Movable : public Object {
    protected: 
        obj_speeds object_speeds;
        bool in_air;

    public: 
        void init_object(float x_pos, float y_pos, float o_width, float o_height, char obj_type);

        obj_speeds get_obj_speeds() const;

        bool in_air_state() const;

        void change_horizontal_speed(float dx);
        void change_vertical_speed(float dy);

        void set_air_state(bool state);
        void set_horiz_speed(float vx);
        void set_vert_speed(float vy);  
};

// class Mario : Movables {
//     private:
// };


#endif