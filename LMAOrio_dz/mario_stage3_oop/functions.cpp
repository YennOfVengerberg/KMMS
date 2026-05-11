#include "functions.hpp"
#include "obj_types.hpp"

void Map::clear_map() {
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {   
            map[j][i] = ' ';
        }
        map[j][MAP_WIDTH] = '\0';
    }
}

void Map::show_map() {
    for (int j = 0; j < MAP_HEIGHT; j++) {
        std::cout << map[j];
    }
}

void Map::display_score(int score) {
    char c[30];
    sprintf(c, "SCORE: %d", score);
    int len = strlen(c);
    for(int i = 0; i < len; i++) {
        map[1][i+5] = c[i];
    }
}

void set_cursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void create_level(int level, TObject* &bricks, int &bricks_number, 
    TObject* &movables, int &movables_number, int &score, int &max_level, TObject &memerio) {
    system("color 1F");

    delete[] bricks;
    bricks = nullptr;
    bricks_number = 0;

    delete[] movables;
    movables = nullptr;
    movables_number = 0;

    init_object(&memerio, 39, 10, 3, 3, '@');
    score = 0;

    if (level == 1)
    {
        init_object(get_new_object(bricks, bricks_number),  0, 21, 207, 4, obj_types::brick);

            init_object(get_new_object(bricks, bricks_number), 48, 13, 3, 2, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 60, 13, 3, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 63, 13, 3, 2, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 66, 13, 3, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 69, 13, 3, 2, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 72, 13, 3, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 66, 5, 3, 2, obj_types::question_brick);

        init_object(get_new_object(bricks, bricks_number), 84, 17, 6, 2, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 85, 19, 4, 2, obj_types::brick);

        init_object(get_new_object(bricks, bricks_number), 114, 15, 6, 2, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 115, 17, 4, 4, obj_types::brick);

        init_object(get_new_object(bricks, bricks_number), 138, 13, 6, 2, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 139, 15, 4, 6, obj_types::brick);

        init_object(get_new_object(bricks, bricks_number), 171, 13, 6, 2, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 172, 15, 4, 6, obj_types::brick);
        // --
        init_object(get_new_object(bricks, bricks_number),  213, 21, 45, 4, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 231, 13, 3, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 234, 13, 3, 2, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 237, 13, 3, 2, obj_types::brick);
                init_object(get_new_object(bricks, bricks_number), 240, 5, 24, 2, obj_types::brick);
        // --
        init_object(get_new_object(bricks, bricks_number),  267, 21, 192, 4, obj_types::brick);
                init_object(get_new_object(bricks, bricks_number), 273, 5, 9, 2, obj_types::brick);
                init_object(get_new_object(bricks, bricks_number), 282, 5, 3, 2, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 282, 13, 3, 2, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 300, 13, 6, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 318, 13, 3, 2, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 327, 13, 3, 2, obj_types::question_brick);
                init_object(get_new_object(bricks, bricks_number), 327, 5, 3, 2, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 336, 13, 3, 2, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 354, 13, 3, 2, obj_types::brick);
                init_object(get_new_object(bricks, bricks_number), 363, 5, 9, 2, obj_types::brick);
                init_object(get_new_object(bricks, bricks_number), 384, 5, 3, 2, obj_types::brick);
                init_object(get_new_object(bricks, bricks_number), 387, 5, 3, 2, obj_types::question_brick);
                init_object(get_new_object(bricks, bricks_number), 390, 5, 3, 2, obj_types::question_brick);
                init_object(get_new_object(bricks, bricks_number), 393, 5, 3, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 387, 13, 6, 2, obj_types::brick);
            //лестница
            init_object(get_new_object(bricks, bricks_number), 402, 19, 12, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 405, 17, 9, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 408, 15, 6, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 411, 13, 3, 2, obj_types::brick);

            init_object(get_new_object(bricks, bricks_number), 420, 13, 3, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 420, 15, 6, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 420, 17, 9, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 420, 19, 12, 2, obj_types::brick);

            init_object(get_new_object(bricks, bricks_number), 444, 19, 15, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 447, 17, 12, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 450, 15, 9, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 453, 13, 6, 2, obj_types::brick);
        // --
        init_object(get_new_object(bricks, bricks_number), 465, 21, 165, 4, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 465, 13, 3, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 465, 15, 6, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 465, 17, 9, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 465, 19, 12, 2, obj_types::brick);

            init_object(get_new_object(bricks, bricks_number), 489, 17, 6, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 490, 19, 4, 2, obj_types::brick);

            init_object(get_new_object(bricks, bricks_number), 504, 13, 6, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 510, 13, 3, 2, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 513, 13, 3, 2, obj_types::brick);

            init_object(get_new_object(bricks, bricks_number), 537, 17, 6, 2, obj_types::brick  );
            init_object(get_new_object(bricks, bricks_number), 538, 19, 4, 2, obj_types::brick);
            // лестница большая
            init_object(get_new_object(bricks, bricks_number), 543, 19, 27, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 546, 17, 24, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 549, 15, 21, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 552, 13, 18, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 555, 11, 15, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 558,  9, 12, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 561,  7,  9, 2, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 564,  5,  6, 2, obj_types::brick);

            // замок
            init_object(get_new_object(bricks, bricks_number), 600, 16, 10, 5, obj_types::win_zone);
                init_object(get_new_object(bricks, bricks_number), 600, 15, 1, 1, obj_types::win_zone);
                init_object(get_new_object(bricks, bricks_number), 609, 15, 1, 1, obj_types::win_zone);
                init_object(get_new_object(bricks, bricks_number), 604, 17, 2, 4, obj_types::empty_brick);
            init_object(get_new_object(bricks, bricks_number), 602, 12, 6, 4, obj_types::win_zone);
                init_object(get_new_object(bricks, bricks_number), 602, 11, 1, 1, obj_types::win_zone);
                init_object(get_new_object(bricks, bricks_number), 604, 11, 2, 1, obj_types::win_zone);
                init_object(get_new_object(bricks, bricks_number), 607, 11, 1, 1, obj_types::win_zone);
                init_object(get_new_object(bricks, bricks_number), 603, 13, 1, 2, obj_types::empty_brick);
                init_object(get_new_object(bricks, bricks_number), 606, 13, 1, 2, obj_types::empty_brick);

        init_object(get_new_object(movables, movables_number), 66, 16, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 121, 16, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 153, 16, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 159, 16, 3, 2, obj_types::enemy);

            init_object(get_new_object(movables, movables_number), 238, 1, 3, 2, obj_types::enemy);
            init_object(get_new_object(movables, movables_number), 246, 1, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 288, 16, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 294, 16, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 321, 16, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 342, 16, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 348, 16, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 370, 16, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 376, 16, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 385, 16, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 391, 16, 3, 2, obj_types::enemy);

        init_object(get_new_object(movables, movables_number), 522, 16, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 526, 16, 3, 2, obj_types::enemy);

    }

    if(level == 2) {
        init_object(get_new_object(bricks, bricks_number), 20, 20, 40, 5, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 30, 10, 5, 3, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 50, 10, 5, 3, obj_types::question_brick);
        init_object(get_new_object(bricks, bricks_number), 60, 15, 40, 10, obj_types::brick);
            init_object(get_new_object(bricks, bricks_number), 60, 5, 10, 3, obj_types::empty_brick);
            init_object(get_new_object(bricks, bricks_number), 70, 5, 5, 3, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 75, 5, 5, 3, obj_types::empty_brick);
            init_object(get_new_object(bricks, bricks_number), 80, 5, 5, 3, obj_types::question_brick);
            init_object(get_new_object(bricks, bricks_number), 85, 5, 10, 3, obj_types::empty_brick);
        init_object(get_new_object(bricks, bricks_number), 100, 20, 20, 5, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 120, 15, 10, 10, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 150, 20, 40, 5, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 210, 15, 10, 10, obj_types::win_zone);

        init_object(get_new_object(movables, movables_number), 25, 10, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 80, 10, 3, 2, obj_types::enemy);
    }
    if(level == 3) {
        init_object(get_new_object(bricks, bricks_number), 20, 20, 40, 5, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 60, 15, 10, 10, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 80, 20, 20, 5, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 120, 15, 10, 10, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 155, 20, 40, 5, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 210, 15, 10, 10, obj_types::win_zone);

        init_object(get_new_object(movables, movables_number), 25, 10, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 80, 10, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 65, 10, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 120, 10, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 160, 10, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 175, 10, 3, 2, obj_types::enemy);

    }
    if(level == 4) {
        init_object(get_new_object(bricks, bricks_number), 20, 20, 40, 5, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 80, 20, 15, 5, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 120, 15, 15, 10, obj_types::brick);
        init_object(get_new_object(bricks, bricks_number), 160, 10, 15, 15, obj_types::win_zone);

        init_object(get_new_object(movables, movables_number), 25, 10, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 50, 10, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 80, 10, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 90, 10, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 120, 10, 3, 2, obj_types::enemy);
        init_object(get_new_object(movables, movables_number), 130, 10, 3, 2, obj_types::enemy);
    }
    
    max_level = 3;
}


void player_collision(TObject* &movables, int &movables_number, 
    int &bricks_number, TObject* &bricks, int &score, int &level, int &max_level, TObject &memerio) {
    for(int i = 0; i < movables_number; i++) {
        if(is_collision(memerio, movables[i])) {
            if(movables[i].c_type == obj_types::enemy) {
                if(memerio.in_air == true && memerio.vert_speed > 0 
                    && memerio.y + memerio.height < movables[i].y + movables[i].height * 0.5) {
                        delete_obj(movables, movables_number, i);
                        i--;
                        score += 50;
                        continue;
                    } else 
                        player_died(level, bricks, bricks_number, movables, movables_number, score, max_level, memerio);
            }

            if(movables[i].c_type == obj_types::money) {
                delete_obj(movables, movables_number, i);
                i--;
                score += 100;
                continue;
            }
        }
    }
}

void player_died(int level, TObject* &bricks, int &bricks_number, 
    TObject* &movables, int &movables_number, int &score, int &max_level, TObject &memerio) {
    system("color 4F");
    Sleep(500);
    create_level(level, bricks, bricks_number, movables, movables_number, score, max_level, memerio);
}

void vert_move_object(TObject *obj, TObject* &bricks, TObject* &movables, 
    int &bricks_number, int &movables_number, int &score, int &level, int &max_level, TObject &memerio) {
    obj->in_air = true;
    obj->vert_speed += 0.05;
    set_object_pos(obj, obj->x, obj->y + obj->vert_speed);

    for(int i = 0; i < bricks_number; i++ ) {    
        if(is_collision(*obj, bricks[i] ) ) {
            if(obj->vert_speed > 0)
                obj->in_air = false;

            if(bricks[i].c_type == obj_types::question_brick && obj->vert_speed < 0 && obj == &memerio) {
                bricks[i].c_type = obj_types::empty_brick;
                init_object(get_new_object(movables, movables_number), bricks[i].x, bricks[i].y-3, 3, 2, obj_types::money);
                movables[movables_number - 1].vert_speed = -0.7;
            }

            obj->y -= obj->vert_speed;
            obj->vert_speed = 0;

            if(bricks[i].c_type == obj_types::win_zone) {
                level++;
                if(level > max_level) {
                    printf("w w w w w w w wwin win win w w w w w");
                    level = 1;
                } 
                system("color 2F");
                Sleep(1000);

                create_level(level, bricks, bricks_number, movables, movables_number, score, max_level, memerio);
            }
            break;
        }
    }
}

void horizon_move_object(TObject *obj, TObject* &bricks, TObject* &movables, 
    int &bricks_number, int &movables_number, int &score, int &level, int &max_level, TObject &memerio) {
    obj->x += obj->horiz_speed;

    for(int i = 0; i < bricks_number; i++) {
        if(is_collision(obj[0], bricks[i])) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
            return;
        }

    }
    if(obj->c_type == obj_types::enemy) { 
        TObject temp = *obj;
        vert_move_object(&temp, bricks, movables, bricks_number, movables_number, score, level, max_level, memerio);
        if(temp.in_air == true) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
        }
    }
}

void horizontal_move_map(float dx, TObject* &bricks, TObject* &movables, 
    int bricks_number, int movables_number, TObject &memerio) {
    memerio.x -= dx;
    for(int i = 0; i < bricks_number; i++) {
        if(is_collision(memerio, bricks[i])) {
            memerio.x += dx;
            return;
        }
    }
    memerio.x += dx;

    for(int i = 0; i < bricks_number; i++) 
        bricks[i].x += dx;
    for(int i = 0; i < movables_number; i++)
        movables[i].x += dx;
}

void Map::put_object_on_map(TObject obj) {
    int ix = static_cast<int>(round(obj.x));
    int iy = static_cast<int>(round(obj.y));
    int i_width = static_cast<int>(round(obj.width));
    int i_height = static_cast<int>(round(obj.height));

    for(int i = ix; i < (ix + i_width); i++) 
        for(int j = iy; j < (iy + i_height); j++)
            if(is_pos_in_map(i, j))
                map[j][i] = obj.c_type;
}

void set_object_pos(TObject *obj, float x_pos, float y_pos) {
    obj->x = x_pos;
    obj->y = y_pos;
}

bool is_pos_in_map(int x, int y) {
    return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
}

bool is_collision(TObject obj1, TObject obj2) {
    return (obj1.x + obj1.width > obj2.x && obj1.x < obj2.x + obj2.width && 
            obj1.y + obj1.height > obj2.y && obj1.y < obj2.y + obj2.height); 
}


void init_object(TObject *obj, float x_pos, float y_pos, float o_width, float o_height, char obj_type) {
    set_object_pos(obj, x_pos, y_pos);
    obj->width = o_width;
    obj->height = o_height;
    obj->vert_speed = 0;
    obj->c_type = obj_type;
    obj->horiz_speed = 0.2;
}

TObject *get_new_object(TObject* &obj_arr, int &obj_number) {
    obj_number++;
    TObject *temp_arr = new TObject[obj_number];
    for(int i = 0; i < obj_number-1; i++) {
        temp_arr[i] = obj_arr[i];
    }
    delete[] obj_arr;
    obj_arr = temp_arr;
    return &obj_arr[obj_number-1];
}

void delete_obj(TObject* &obj_arr, int &obj_number, int i) {
    obj_number--;
    obj_arr[i] = obj_arr[obj_number];
    TObject *temp_arr = new TObject[obj_number];
    for(int i = 0; i < obj_number; i++) {
        temp_arr[i] = obj_arr[i];
    }
    delete[] obj_arr;
    obj_arr = temp_arr;
}
