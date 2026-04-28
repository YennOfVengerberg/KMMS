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
    BOOL in_air;
    char c_type;
} TObject;

char map[map_height][map_width+1];
TObject memerio;
TObject *brick = NULL;
int brick_length;
int level = 1;

void clear_map() {
    for(int i = 0; i < map_width; i++) 
        map[0][i] = ' ';
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

void init_object(TObject *obj, float x_pos, float y_pos, float o_width, float o_height, char obj_type) {
    set_object_pos(obj, x_pos, y_pos);
    (*obj).width = o_width;
    (*obj).height = o_height;
    (*obj).vert_speed = 0;
    (*obj).c_type = obj_type;
}

BOOL is_collision(TObject obj1, TObject obj2);
void create_level(int level);

void vert_move_object(TObject *obj) {
    (*obj).in_air = TRUE;
    (*obj).vert_speed += 0.05;
    set_object_pos(obj, (*obj).x, (*obj).y + (*obj).vert_speed);

    for(int i = 0; i < brick_length; i++ ) {    
        if(is_collision(*obj, brick[i] ) ) {
            (*obj).y -= (*obj).vert_speed;
            (*obj).vert_speed = 0;
            (*obj).in_air = FALSE;
            if(brick[i].c_type == 'w') {
                level++;
                if(level > 2) printf("w w w w w w w wwin win win w w w w w"); 
                create_level(level);
                Sleep(1000);
            }
            break;
        }
    }
}

void create_level(int level) {
    init_object(&memerio, 39, 10, 3, 3, '@');

    if(level == 1) {
        brick_length = 6;
        brick = (TObject*)realloc(brick, sizeof(*brick) * brick_length);
        init_object(brick+0, 20, 20, 40, 5, '2');
        init_object(brick+1, 60, 15, 10, 10, '2');
        init_object(brick+2, 80, 20, 20, 5, '2');
        init_object(brick+3, 120, 15, 10, 10, '2');
        init_object(brick+4, 155, 20, 40, 5, '2');
        init_object(brick+5, 210, 15, 10, 10, 'w');
    }
    if(level == 2) {
        brick_length = 4;
        brick = (TObject*)realloc(brick, sizeof(*brick) * brick_length);
        init_object(brick+0, 20, 20, 40, 5, '2');
        init_object(brick+1, 80, 20, 15, 5, '2');
        init_object(brick+2, 120, 15, 15, 10, '2');
        init_object(brick+3, 160, 10, 15, 15, 'w');
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
                map[j][i] = obj.c_type;
}

void set_cursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void horizontal_move_map(float dx) {
    memerio.x -= dx;
    for(int i = 0; i < brick_length; i++) {
        if(is_collision(memerio, brick[i])) {
            memerio.x += dx;
            return;
        }
    }
    memerio.x += dx;

    for(int i = 0; i < brick_length; i++) 
        brick[i].x += dx;
}

BOOL is_collision(TObject obj1, TObject obj2) {
    return (obj1.x + obj1.width > obj2.x && obj1.x < obj2.x + obj2.width && 
            obj1.y + obj1.width > obj2.y && obj1.y < obj2.y + obj2.height); 
}

int main() {
    
    create_level(level);

    system("color 1F");

    do  {
        clear_map();

        if(memerio.in_air == FALSE && GetKeyState(VK_UP) < 0) memerio.vert_speed = -1.0;
        if(GetKeyState(VK_LEFT) < 0) horizontal_move_map(1);
        if(GetKeyState(VK_RIGHT) < 0) horizontal_move_map(-1);

        if(memerio.y > map_height) create_level(level);

        vert_move_object(&memerio);
        for(int i = 0; i < brick_length; i++) {
            put_object_on_map(brick[i]);
        }
        put_object_on_map(memerio);

        set_cursor(0, 0);
        show_map();

        Sleep(10);
    } while(GetKeyState(VK_ESCAPE) >= 0);
    return 0;
    
}