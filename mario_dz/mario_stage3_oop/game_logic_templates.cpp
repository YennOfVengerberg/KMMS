//#include "game_logic.hpp"
#include "game_logic.cpp"

template Brick *Game::get_new_object<Brick>(Brick* &obj_arr, int &obj_number);
template void Game::delete_obj<Brick>(Brick* &obj_arr, int &obj_number, int i);

template Movable *Game::get_new_object<Movable>(Movable* &obj_arr, int &obj_number);
template void Game::delete_obj<Movable>(Movable* &obj_arr, int &obj_number, int i);