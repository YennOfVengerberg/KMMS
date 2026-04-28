#include <stdio.h>
#include <cstdlib>

#include <math.h>
#include <windows.h>

#define map_width 80
#define map_height 25

typedef struct SObject {
    float x, y;
    float height, width;
    float vert_speed;
} TObject;

char map[map_height][map_width+1];
TObject memerio;
TObject brick[1];

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
    (*obj).vert_speed = 0;
}

BOOL is_collision(TObject obj1, TObject obj2);

void vert_move_object(TObject *obj) {
    (*obj).vert_speed += 0.05;
    set_object_pos(obj, (*obj).x, (*obj).y + (*obj).vert_speed);
    if(is_collision(*obj, brick[0] ) ) {
        (*obj).y -= (*obj).vert_speed;
        (*obj).vert_speed = 0;
    }
}

BOOL is_pos_in_map(int x, int y) {
    return (x >= 0 && x < map_width && y >= 0 && y < map_height);
}

void put_object_on_map(TObject obj) {
    int ix = int(round(obj.x));
    int iy = int(round(obj.y));
    int i_width = int(round(obj.width));
    int i_heigth = int(round(obj.height));

    for(int i = ix; i < (ix + i_width); i++) 
        for(int j = iy; j < (iy + i_heigth); j++)
            if(is_pos_in_map(i, j))
                map[j][i] = '@';
}

void set_cursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

BOOL is_collision(TObject obj1, TObject obj2) {
    return (obj1.x + obj1.width > obj2.x && obj1.x < obj2.x + obj2.width && 
            obj1.y + obj1.width > obj2.y && obj1.y < obj2.y + obj2.height); 
}

int main() {
    init_object(&memerio, 39, 10, 3, 3);
    init_object(brick, 20, 20, 40, 5);

    do  {
        clear_map();
        vert_move_object(&memerio);
        put_object_on_map(brick[0]);
        put_object_on_map(memerio);

        set_cursor(0, 0);
        show_map();

        Sleep(10);
    } while(GetKeyState(VK_ESCAPE) >= 0);
    return 0;
    
}