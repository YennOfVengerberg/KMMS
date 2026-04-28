#include <stdio.h>
#include <cstdlib>

#include <math.h>

#define map_width 80
#define map_height 25

typedef struct SObject {
    float x, y;
    float height, width;
} TObject;

char map[map_height][map_width+1];
TObject memerio;

void clear_map() {
    for(int i = 0; i < map_width; i++) 
        map[0][i] = '.';
    for(int j = 1; j < map_height; j++)
        sprintf(map[j], map[0]);
}

void show_map() {
    map[map_height - 1][map_width - 1] = '\0';
    for(int j = 0; j < map_height; j++)
        printf("%s", map[j]);
}

void set_object_pos(TObject *obj, float x_pos, float y_pos) {
    (*obj).x = x_pos;
    (*obj).y = y_pos;
}

void init_object(TObject *obj, float x_pos, float y_pos, float o_width, float o_height) {
    set_object_pos(obj, x_pos, y_pos);
    (*obj).width = o_width;
    (*obj).height = o_height;
}

void put_object_on_map(TObject obj) {
    int ix = int(round(obj.x));
    int iy = int(round(obj.y));
    int i_width = int(round(obj.width));
    int i_heigth = int(round(obj.height));

    for(int i = ix; i < (ix + i_width); i++) 
        for(int j = iy; j < (iy + i_heigth); j++)
            map[j][i] = '@';
}

int main() {
    init_object(&memerio, 39, 10, 3, 3);
    clear_map();
    put_object_on_map(memerio);
    show_map();
    return 0;
    
}