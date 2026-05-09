#ifndef OBJ_TYPES
#define OBJ_TYPES

#include "functions.hpp"

enum obj_types: char {
    player = '@',
    brick = '#',
    question_brick = '?',
    empty_brick = '-',
    win_zone = 'w',
    money = '$',
    enemy = 'o'
};

#endif