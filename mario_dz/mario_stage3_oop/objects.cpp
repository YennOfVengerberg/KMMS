#include "objects.hpp"

void Object::set_object_pos(float x_pos, float y_pos) {
    object_dimensions.x = x_pos;
    object_dimensions.y = y_pos;
}

void Object::init_object(float x_pos, float y_pos, float o_width, float o_height, char obj_type) {
    set_object_pos(x_pos, y_pos);
    object_dimensions.width = o_width;
    object_dimensions.height = o_height;
    object_type = obj_type;
}

void Movable::init_object(float x_pos, float y_pos, float o_width, float o_height, char obj_type) {
    Object::init_object(x_pos, y_pos, o_width, o_height, obj_type);
    object_speeds.vert_speed = 0;
    object_speeds.horiz_speed = 0.2;
}
// ----------

bool Movable::in_air_state() const {
    return in_air;
}
// ---------

char Object::get_object_type() const {
    return object_type;
}
// ---------

obj_dimensions Object::get_obj_dimensions() const {
    return object_dimensions;
}


obj_speeds Movable::get_obj_speeds() const {
    return object_speeds;
}
// ---------

void Movable::change_horizontal_speed(float dx) {
    if(dx == 0)
        object_speeds.horiz_speed = 0;
    else
        object_speeds.horiz_speed += dx;
}

void Movable::change_vertical_speed(float dy) {
    if(dy == 0)
        object_speeds.vert_speed = 0;
    else
        object_speeds.vert_speed += dy;
}
// ---------

void Object::move_horizontal(float dx) {
    object_dimensions.x += dx;
}

void Object::move_vertical(float dy) {
    object_dimensions.y += dy;
}
// ---------

void Movable::set_air_state(bool state) {
    in_air = state;
}

void Brick::set_object_type(char new_type) {
    object_type = new_type;
}

void Movable::set_horiz_speed(float vx) {
    object_speeds.horiz_speed = vx;
}

void Movable::set_vert_speed(float vy) {
    object_speeds.vert_speed = vy;
}