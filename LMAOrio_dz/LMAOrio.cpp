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
    float horiz_speed;
} TObject;

char map[map_height][map_width+1];

TObject memerio;

TObject *brick = NULL;
int bricks_number;

TObject *movables = NULL;
int movables_number;

int level = 1;
int score;
int max_level;

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
    (*obj).horiz_speed = 0.2;
}

BOOL is_collision(TObject obj1, TObject obj2);
void create_level(int level);

void player_died() {
    system("color 4F");
    Sleep(500);
    create_level(level);
}

TObject *get_new_brick() {
    bricks_number++;
    brick = (TObject*)realloc(brick, sizeof(*brick) * bricks_number);
    return brick + bricks_number - 1;
}

TObject *get_new_movable() {
    movables_number++;
    movables = (TObject*)realloc(movables, sizeof(*movables) * movables_number);
    return movables + movables_number - 1;
}

void vert_move_object(TObject *obj) {
    (*obj).in_air = TRUE;
    (*obj).vert_speed += 0.05;
    set_object_pos(obj, (*obj).x, (*obj).y + (*obj).vert_speed);

    for(int i = 0; i < bricks_number; i++ ) {    
        if(is_collision(*obj, brick[i] ) ) {
            if(obj[0].vert_speed > 0)
                obj[0].in_air = FALSE;

            if(brick[i].c_type == '?' && obj[0].vert_speed < 0 && obj == &memerio) {
                brick[i].c_type = '-';
                init_object(get_new_movable(), brick[i].x, brick[i].y-3, 3, 2, '$');
                movables[movables_number - 1].vert_speed = -0.7;
            }

            (*obj).y -= (*obj).vert_speed;
            (*obj).vert_speed = 0;

            if(brick[i].c_type == 'w') {
                level++;
                if(level > max_level) {
                    printf("w w w w w w w wwin win win w w w w w");
                    level = 1;
                } 
                system("color 2F");
                Sleep(1000);

                create_level(level);
            }
            break;
        }
    }
}

void display_score() {
    char c[30];
    sprintf(c, "SCORE: %d", score);
    int len = strlen(c);
    for(int i = 0; i < len; i++) {
        map[1][i+5] = c[i];
    }
}

void create_level(int level) {
    system("color 1F");

    bricks_number = 0;
    brick = (TObject*)realloc(brick, 0);

    movables_number = 0;
    movables = (TObject*)realloc(movables, 0);

    init_object(&memerio, 39, 10, 3, 3, '@');
    score = 0;

    if (level == 1)
    {
        init_object(get_new_brick(),  0, 21, 207, 4, '#');

            init_object(get_new_brick(), 48, 13, 3, 2, '?');
            init_object(get_new_brick(), 60, 13, 3, 2, '#');
            init_object(get_new_brick(), 63, 13, 3, 2, '?');
            init_object(get_new_brick(), 66, 13, 3, 2, '#');
            init_object(get_new_brick(), 69, 13, 3, 2, '?');
            init_object(get_new_brick(), 72, 13, 3, 2, '#');
            init_object(get_new_brick(), 66, 5, 3, 2, '?');

        init_object(get_new_brick(), 84, 17, 6, 2, '#');
        init_object(get_new_brick(), 85, 19, 4, 2, '#');

        init_object(get_new_brick(), 114, 15, 6, 2, '#');
        init_object(get_new_brick(), 115, 17, 4, 4, '#');

        init_object(get_new_brick(), 138, 13, 6, 2, '#');
        init_object(get_new_brick(), 139, 15, 4, 6, '#');

        init_object(get_new_brick(), 171, 13, 6, 2, '#');
        init_object(get_new_brick(), 172, 15, 4, 6, '#');
        // --
        init_object(get_new_brick(),  213, 21, 45, 4, '#');
            init_object(get_new_brick(), 231, 13, 3, 2, '#');
            init_object(get_new_brick(), 234, 13, 3, 2, '?');
            init_object(get_new_brick(), 237, 13, 3, 2, '#');
                init_object(get_new_brick(), 240, 5, 24, 2, '#');
        // --
        init_object(get_new_brick(),  267, 21, 192, 4, '#');
                init_object(get_new_brick(), 273, 5, 9, 2, '#');
                init_object(get_new_brick(), 282, 5, 3, 2, '?');
            init_object(get_new_brick(), 282, 13, 3, 2, '?');
            init_object(get_new_brick(), 300, 13, 6, 2, '#');
            init_object(get_new_brick(), 318, 13, 3, 2, '?');
            init_object(get_new_brick(), 327, 13, 3, 2, '?');
                init_object(get_new_brick(), 327, 5, 3, 2, '?');
            init_object(get_new_brick(), 336, 13, 3, 2, '?');
            init_object(get_new_brick(), 354, 13, 3, 2, '#');
                init_object(get_new_brick(), 363, 5, 9, 2, '#');
                init_object(get_new_brick(), 384, 5, 3, 2, '#');
                init_object(get_new_brick(), 387, 5, 3, 2, '?');
                init_object(get_new_brick(), 390, 5, 3, 2, '?');
                init_object(get_new_brick(), 393, 5, 3, 2, '#');
            init_object(get_new_brick(), 387, 13, 6, 2, '#');
            //лестница
            init_object(get_new_brick(), 402, 19, 12, 2, '#');
            init_object(get_new_brick(), 405, 17, 9, 2, '#');
            init_object(get_new_brick(), 408, 15, 6, 2, '#');
            init_object(get_new_brick(), 411, 13, 3, 2, '#');

            init_object(get_new_brick(), 420, 13, 3, 2, '#');
            init_object(get_new_brick(), 420, 15, 6, 2, '#');
            init_object(get_new_brick(), 420, 17, 9, 2, '#');
            init_object(get_new_brick(), 420, 19, 12, 2, '#');

            init_object(get_new_brick(), 444, 19, 15, 2, '#');
            init_object(get_new_brick(), 447, 17, 12, 2, '#');
            init_object(get_new_brick(), 450, 15, 9, 2, '#');
            init_object(get_new_brick(), 453, 13, 6, 2, '#');
        // --
        init_object(get_new_brick(), 465, 21, 165, 4, '#');
            init_object(get_new_brick(), 465, 13, 3, 2, '#');
            init_object(get_new_brick(), 465, 15, 6, 2, '#');
            init_object(get_new_brick(), 465, 17, 9, 2, '#');
            init_object(get_new_brick(), 465, 19, 12, 2, '#');

            init_object(get_new_brick(), 489, 17, 6, 2, '#');
            init_object(get_new_brick(), 490, 19, 4, 2, '#');

            init_object(get_new_brick(), 504, 13, 6, 2, '#');
            init_object(get_new_brick(), 510, 13, 3, 2, '?');
            init_object(get_new_brick(), 513, 13, 3, 2, '#');

            init_object(get_new_brick(), 537, 17, 6, 2, '#');
            init_object(get_new_brick(), 538, 19, 4, 2, '#');
            // лестница большая
            init_object(get_new_brick(), 543, 19, 27, 2, '#');
            init_object(get_new_brick(), 546, 17, 24, 2, '#');
            init_object(get_new_brick(), 549, 15, 21, 2, '#');
            init_object(get_new_brick(), 552, 13, 18, 2, '#');
            init_object(get_new_brick(), 555, 11, 15, 2, '#');
            init_object(get_new_brick(), 558,  9, 12, 2, '#');
            init_object(get_new_brick(), 561,  7,  9, 2, '#');
            init_object(get_new_brick(), 564,  5,  6, 2, '#');

            // замок
            init_object(get_new_brick(), 600, 16, 10, 5, 'w');
                init_object(get_new_brick(), 600, 15, 1, 1, 'w');
                init_object(get_new_brick(), 609, 15, 1, 1, 'w');
                init_object(get_new_brick(), 604, 17, 2, 4, '-');
            init_object(get_new_brick(), 602, 12, 6, 4, 'w');
                init_object(get_new_brick(), 602, 11, 1, 1, 'w');
                init_object(get_new_brick(), 604, 11, 2, 1, 'w');
                init_object(get_new_brick(), 607, 11, 1, 1, 'w');
                init_object(get_new_brick(), 603, 13, 1, 2, '-');
                init_object(get_new_brick(), 606, 13, 1, 2, '-');

        init_object(get_new_movable(), 66, 16, 3, 2, 'o');
        init_object(get_new_movable(), 121, 16, 3, 2, 'o');
        init_object(get_new_movable(), 153, 16, 3, 2, 'o');
        init_object(get_new_movable(), 159, 16, 3, 2, 'o');

            init_object(get_new_movable(), 238, 1, 3, 2, 'o');
            init_object(get_new_movable(), 246, 1, 3, 2, 'o');
        init_object(get_new_movable(), 288, 16, 3, 2, 'o');
        init_object(get_new_movable(), 294, 16, 3, 2, 'o');
        init_object(get_new_movable(), 321, 16, 3, 2, 'o');
        init_object(get_new_movable(), 342, 16, 3, 2, 'o');
        init_object(get_new_movable(), 348, 16, 3, 2, 'o');
        init_object(get_new_movable(), 370, 16, 3, 2, 'o');
        init_object(get_new_movable(), 376, 16, 3, 2, 'o');
        init_object(get_new_movable(), 385, 16, 3, 2, 'o');
        init_object(get_new_movable(), 391, 16, 3, 2, 'o');

        init_object(get_new_movable(), 522, 16, 3, 2, 'o');
        init_object(get_new_movable(), 526, 16, 3, 2, 'o');

    }

    if(level == 2) {
        init_object(get_new_brick(), 20, 20, 40, 5, '2');
            init_object(get_new_brick(), 30, 10, 5, 3, '?');
            init_object(get_new_brick(), 50, 10, 5, 3, '?');
        init_object(get_new_brick(), 60, 15, 40, 10, '2');
            init_object(get_new_brick(), 60, 5, 10, 3, '-');
            init_object(get_new_brick(), 70, 5, 5, 3, '?');
            init_object(get_new_brick(), 75, 5, 5, 3, '-');
            init_object(get_new_brick(), 80, 5, 5, 3, '?');
            init_object(get_new_brick(), 85, 5, 10, 3, '-');
        init_object(get_new_brick(), 100, 20, 20, 5, '2');
        init_object(get_new_brick(), 120, 15, 10, 10, '2');
        init_object(get_new_brick(), 150, 20, 40, 5, '2');
        init_object(get_new_brick(), 210, 15, 10, 10, 'w');

        init_object(get_new_movable(), 25, 10, 3, 2, 'o');
        init_object(get_new_movable(), 80, 10, 3, 2, 'o');
    }
    if(level == 3) {
        init_object(get_new_brick(), 20, 20, 40, 5, '2');
        init_object(get_new_brick(), 60, 15, 10, 10, '2');
        init_object(get_new_brick(), 80, 20, 20, 5, '2');
        init_object(get_new_brick(), 120, 15, 10, 10, '2');
        init_object(get_new_brick(), 155, 20, 40, 5, '2');
        init_object(get_new_brick(), 210, 15, 10, 10, 'w');

        init_object(get_new_movable(), 25, 10, 3, 2, 'o');
        init_object(get_new_movable(), 80, 10, 3, 2, 'o');
        init_object(get_new_movable(), 65, 10, 3, 2, 'o');
        init_object(get_new_movable(), 120, 10, 3, 2, 'o');
        init_object(get_new_movable(), 160, 10, 3, 2, 'o');
        init_object(get_new_movable(), 175, 10, 3, 2, 'o');
        
    }
    if(level == 4) {
        init_object(get_new_brick(), 20, 20, 40, 5, '2');
        init_object(get_new_brick(), 80, 20, 15, 5, '2');
        init_object(get_new_brick(), 120, 15, 15, 10, '2');
        init_object(get_new_brick(), 160, 10, 15, 15, 'w');

        init_object(get_new_movable(), 25, 10, 3, 2, 'o');
        init_object(get_new_movable(), 50, 10, 3, 2, 'o');
        init_object(get_new_movable(), 80, 10, 3, 2, 'o');
        init_object(get_new_movable(), 90, 10, 3, 2, 'o');
        init_object(get_new_movable(), 120, 10, 3, 2, 'o');
        init_object(get_new_movable(), 130, 10, 3, 2, 'o');
    }
    
    max_level = 3;
}

void delete_movable(int i) {
    movables_number--;
    movables[i] = movables[movables_number];
    movables = (TObject*)realloc(movables, sizeof(*movables) * movables_number);
}

void player_collision() {
    for(int i = 0; i < movables_number; i++) {
        if(is_collision(memerio, movables[i])) {
            if(movables[i].c_type == 'o') {
                if(memerio.in_air == TRUE && memerio.vert_speed > 0 
                    && memerio.y + memerio.height < movables[i].y + movables[i].height * 0.5) {
                        delete_movable(i);
                        i--;
                        score += 50;
                        continue;
                    } else 
                        player_died();
            }

            if(movables[i].c_type == '$') {
                delete_movable(i);
                i--;
                score += 100;
                continue;
            }
        }
    }
}

void horizon_move_object(TObject *obj) {
    obj[0].x += obj[0].horiz_speed;

    for(int i = 0; i < bricks_number; i++) {
        if(is_collision(obj[0], brick[i])) {
            obj[0].x -= obj[0].horiz_speed;
            obj[0].horiz_speed = -obj[0].horiz_speed;
            return;
        }

    }
    if(obj[0].c_type == 'o') { 
        TObject temp = *obj;
        vert_move_object(&temp);
        if(temp.in_air == TRUE) {
            obj[0].x -= obj[0].horiz_speed;
            obj[0].horiz_speed = -obj[0].horiz_speed;
        }
    }
}

BOOL is_pos_in_map(int x, int y) {
    return (x >= 0 && x < map_width && y >= 0 && y < map_height);
}

void put_object_on_map(TObject obj) {
    int ix = int(round(obj.x));
    int iy = int(round(obj.y));
    int i_width = int(round(obj.width));
    int i_height = int(round(obj.height));

    for(int i = ix; i < (ix + i_width); i++) 
        for(int j = iy; j < (iy + i_height); j++)
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
    for(int i = 0; i < bricks_number; i++) {
        if(is_collision(memerio, brick[i])) {
            memerio.x += dx;
            return;
        }
    }
    memerio.x += dx;

    for(int i = 0; i < bricks_number; i++) 
        brick[i].x += dx;
    for(int i = 0; i < movables_number; i++)
        movables[i].x += dx;
}

BOOL is_collision(TObject obj1, TObject obj2) {
    return (obj1.x + obj1.width > obj2.x && obj1.x < obj2.x + obj2.width && 
            obj1.y + obj1.height > obj2.y && obj1.y < obj2.y + obj2.height); 
}

int main() {
    
    create_level(level);


    do  {
        clear_map();

        if(memerio.in_air == FALSE && GetKeyState(VK_UP) < 0) memerio.vert_speed = -1.0;
        if(GetKeyState(VK_LEFT) < 0) horizontal_move_map(1);
        if(GetKeyState(VK_RIGHT) < 0) horizontal_move_map(-1);

        if(memerio.y > map_height) player_died();

        vert_move_object(&memerio);
        player_collision();

        for(int i = 0; i < bricks_number; i++) {
            put_object_on_map(brick[i]);
        }
        for(int i = 0; i < movables_number; i++) {
            vert_move_object(movables + i);
            horizon_move_object(movables + i);
            if(movables[i].y > map_height) {
                delete_movable(i);
                i--;
                continue;
            }
            put_object_on_map(movables[i]);
        }

        put_object_on_map(memerio);
        display_score();


        set_cursor(0, 0);
        show_map();

        Sleep(10);
    } while(GetKeyState(VK_ESCAPE) >= 0);
    return 0;
    
}