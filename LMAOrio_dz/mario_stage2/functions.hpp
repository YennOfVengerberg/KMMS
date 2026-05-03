#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <cstdlib>

#include <math.h>
#include <windows.h>

#define MAP_WIDTH 81
#define MAP_HEIGHT 25

struct TObject {
    float x, y;
    float height, width;
    float vert_speed;
    float horiz_speed;
    bool in_air;
    char c_type;
};



#endif