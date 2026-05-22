#include "level_creator.cpp"

template Brick *Level_Creator::get_new_object<Brick>(Brick* &obj_arr, int &obj_number);
template Movable *Level_Creator::get_new_object<Movable>(Movable* &obj_arr, int &obj_number);