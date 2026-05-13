#include "objects.hpp"

void Object::set_object_pos(float x_pos, float y_pos) {
    x = x_pos;
    y = y_pos;
}

void Object::init_object(float x_pos, float y_pos, float o_width, float o_height, char obj_type) {
    set_object_pos(x_pos, y_pos);
    width = o_width;
    height = o_height;
    vert_speed = 0;
    object_type = obj_type;
    horiz_speed = 0.2;
}
// ----------

bool Object::in_air_state() const {
    return in_air;
}
// ---------

char Object::get_object_type() const {
    return object_type;
}
// ---------

std::pair<float, float> Object::get_coordinates() const {
    return {x, y};
}

std::pair<float, float> Object::get_height_width() const {
    return {height, width};
}

std::pair<float, float> Object::get_vert_horiz_speeds() const {
    return {vert_speed, horiz_speed};
}
// ---------

void Object::change_horizontal_speed(float dx) {
    if(dx == 0)
        horiz_speed = 0;
    else
        horiz_speed += dx;
}

void Object::change_vertical_speed(float dy) {
    if(dy == 0)
        vert_speed = 0;
    else
        vert_speed += dy;
}
// ---------

void Object::move_horizontal(float dx) {
    x += dx;
}

void Object::move_vertical(float dy) {
    y += dy;
}
// ---------

void Object::set_air_state(bool state) {
    in_air = state;
}

void Object::set_object_type(char new_type) {
    object_type = new_type;
}

void Object::set_horiz_speed(float vx) {
    horiz_speed = vx;
}

void Object::set_vert_speed(float vy) {
    vert_speed = vy;
}