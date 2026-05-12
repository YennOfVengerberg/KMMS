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

void Map::set_cursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void create_level(int level, Object* &bricks, int &bricks_number, 
    Object* &movables, int &movables_number, int &score, int &max_level, Object &memerio) {
    system("color 1F");

    delete[] bricks;
    bricks = nullptr;
    bricks_number = 0;

    delete[] movables;
    movables = nullptr;
    movables_number = 0;

    memerio.init_object(39, 10, 3, 3, '@');
    score = 0;

    if (level == 1)
    {
        (get_new_object(bricks, bricks_number))->init_object( 0, 21, 207, 4, obj_types::brick);

            (get_new_object(bricks, bricks_number))->init_object(48, 13, 3, 2, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object(60, 13, 3, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object(63, 13, 3, 2, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object(66, 13, 3, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object(69, 13, 3, 2, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object(72, 13, 3, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object(66, 5, 3, 2, obj_types::question_brick);

        (get_new_object(bricks, bricks_number))->init_object(84, 17, 6, 2, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object(85, 19, 4, 2, obj_types::brick);

        (get_new_object(bricks, bricks_number))->init_object(114, 15, 6, 2, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object(115, 17, 4, 4, obj_types::brick);

        (get_new_object(bricks, bricks_number))->init_object(138, 13, 6, 2, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object(139, 15, 4, 6, obj_types::brick);

        (get_new_object(bricks, bricks_number))->init_object(171, 13, 6, 2, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object(172, 15, 4, 6, obj_types::brick);
        // --
        (get_new_object(bricks, bricks_number))->init_object(213, 21, 45, 4, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object(231, 13, 3, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object(234, 13, 3, 2, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object(237, 13, 3, 2, obj_types::brick);
                (get_new_object(bricks, bricks_number))->init_object(240, 5, 24, 2, obj_types::brick);
        // --
        (get_new_object(bricks, bricks_number))->init_object(267, 21, 192, 4, obj_types::brick);
                (get_new_object(bricks, bricks_number))->init_object(273, 5, 9, 2, obj_types::brick);
                (get_new_object(bricks, bricks_number))->init_object(282, 5, 3, 2, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object( 282, 13, 3, 2, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object( 300, 13, 6, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 318, 13, 3, 2, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object( 327, 13, 3, 2, obj_types::question_brick);
                (get_new_object(bricks, bricks_number))->init_object( 327, 5, 3, 2, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object( 336, 13, 3, 2, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object( 354, 13, 3, 2, obj_types::brick);
                (get_new_object(bricks, bricks_number))->init_object( 363, 5, 9, 2, obj_types::brick);
                (get_new_object(bricks, bricks_number))->init_object( 384, 5, 3, 2, obj_types::brick);
                (get_new_object(bricks, bricks_number))->init_object( 387, 5, 3, 2, obj_types::question_brick);
                (get_new_object(bricks, bricks_number))->init_object( 390, 5, 3, 2, obj_types::question_brick);
                (get_new_object(bricks, bricks_number))->init_object( 393, 5, 3, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 387, 13, 6, 2, obj_types::brick);
            //лестница
            (get_new_object(bricks, bricks_number))->init_object( 402, 19, 12, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 405, 17, 9, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 408, 15, 6, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 411, 13, 3, 2, obj_types::brick);

            (get_new_object(bricks, bricks_number))->init_object( 420, 13, 3, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 420, 15, 6, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 420, 17, 9, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 420, 19, 12, 2, obj_types::brick);

            (get_new_object(bricks, bricks_number))->init_object( 444, 19, 15, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 447, 17, 12, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 450, 15, 9, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 453, 13, 6, 2, obj_types::brick);
        // --
        (get_new_object(bricks, bricks_number))->init_object( 465, 21, 165, 4, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 465, 13, 3, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 465, 15, 6, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 465, 17, 9, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 465, 19, 12, 2, obj_types::brick);

            (get_new_object(bricks, bricks_number))->init_object( 489, 17, 6, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 490, 19, 4, 2, obj_types::brick);

            (get_new_object(bricks, bricks_number))->init_object( 504, 13, 6, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 510, 13, 3, 2, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object( 513, 13, 3, 2, obj_types::brick);

            (get_new_object(bricks, bricks_number))->init_object( 537, 17, 6, 2, obj_types::brick  );
            (get_new_object(bricks, bricks_number))->init_object( 538, 19, 4, 2, obj_types::brick);
            // лестница большая
            (get_new_object(bricks, bricks_number))->init_object( 543, 19, 27, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 546, 17, 24, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 549, 15, 21, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 552, 13, 18, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 555, 11, 15, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 558,  9, 12, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 561,  7,  9, 2, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 564,  5,  6, 2, obj_types::brick);

            // замок
            (get_new_object(bricks, bricks_number))->init_object( 600, 16, 10, 5, obj_types::win_zone);
                (get_new_object(bricks, bricks_number))->init_object( 600, 15, 1, 1, obj_types::win_zone);
                (get_new_object(bricks, bricks_number))->init_object( 609, 15, 1, 1, obj_types::win_zone);
                (get_new_object(bricks, bricks_number))->init_object( 604, 17, 2, 4, obj_types::empty_brick);
            (get_new_object(bricks, bricks_number))->init_object( 602, 12, 6, 4, obj_types::win_zone);
                (get_new_object(bricks, bricks_number))->init_object( 602, 11, 1, 1, obj_types::win_zone);
                (get_new_object(bricks, bricks_number))->init_object( 604, 11, 2, 1, obj_types::win_zone);
                (get_new_object(bricks, bricks_number))->init_object( 607, 11, 1, 1, obj_types::win_zone);
                (get_new_object(bricks, bricks_number))->init_object( 603, 13, 1, 2, obj_types::empty_brick);
                (get_new_object(bricks, bricks_number))->init_object( 606, 13, 1, 2, obj_types::empty_brick);

        (get_new_object(movables, movables_number))->init_object( 66, 16, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 121, 16, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 153, 16, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 159, 16, 3, 2, obj_types::enemy);

            (get_new_object(movables, movables_number))->init_object( 238, 1, 3, 2, obj_types::enemy);
            (get_new_object(movables, movables_number))->init_object( 246, 1, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 288, 16, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 294, 16, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 321, 16, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 342, 16, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 348, 16, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 370, 16, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 376, 16, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 385, 16, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 391, 16, 3, 2, obj_types::enemy);

        (get_new_object(movables, movables_number))->init_object( 522, 16, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 526, 16, 3, 2, obj_types::enemy);

    }

    if(level == 2) {
        (get_new_object(bricks, bricks_number))->init_object( 20, 20, 40, 5, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 30, 10, 5, 3, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object( 50, 10, 5, 3, obj_types::question_brick);
        (get_new_object(bricks, bricks_number))->init_object( 60, 15, 40, 10, obj_types::brick);
            (get_new_object(bricks, bricks_number))->init_object( 60, 5, 10, 3, obj_types::empty_brick);
            (get_new_object(bricks, bricks_number))->init_object( 70, 5, 5, 3, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object( 75, 5, 5, 3, obj_types::empty_brick);
            (get_new_object(bricks, bricks_number))->init_object( 80, 5, 5, 3, obj_types::question_brick);
            (get_new_object(bricks, bricks_number))->init_object( 85, 5, 10, 3, obj_types::empty_brick);
        (get_new_object(bricks, bricks_number))->init_object( 100, 20, 20, 5, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object( 120, 15, 10, 10, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object( 150, 20, 40, 5, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object( 210, 15, 10, 10, obj_types::win_zone);

        (get_new_object(movables, movables_number))->init_object( 25, 10, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 80, 10, 3, 2, obj_types::enemy);
    }
    if(level == 3) {
        (get_new_object(bricks, bricks_number))->init_object( 20, 20, 40, 5, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object( 60, 15, 10, 10, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object( 80, 20, 20, 5, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object( 120, 15, 10, 10, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object( 155, 20, 40, 5, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object( 210, 15, 10, 10, obj_types::win_zone);

        (get_new_object(movables, movables_number))->init_object( 25, 10, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 80, 10, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 65, 10, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 120, 10, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 160, 10, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 175, 10, 3, 2, obj_types::enemy);

    }
    if(level == 4) {
        (get_new_object(bricks, bricks_number))->init_object( 20, 20, 40, 5, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object( 80, 20, 15, 5, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object( 120, 15, 15, 10, obj_types::brick);
        (get_new_object(bricks, bricks_number))->init_object( 160, 10, 15, 15, obj_types::win_zone);

        (get_new_object(movables, movables_number))->init_object( 25, 10, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 50, 10, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 80, 10, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 90, 10, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 120, 10, 3, 2, obj_types::enemy);
        (get_new_object(movables, movables_number))->init_object( 130, 10, 3, 2, obj_types::enemy);
    }
    
    max_level = 3;
}


void player_collision(Object* &movables, int &movables_number, 
    int &bricks_number, Object* &bricks, int &score, int &level, int &max_level, Object &memerio) {
    for(int i = 0; i < movables_number; i++) {
        if(is_collision(memerio, movables[i])) {
            if(movables[i].get_object_type() == obj_types::enemy) {
                if(memerio.in_air_state() == true && memerio.get_vert_horiz_speeds().first > 0 
                    && memerio.get_coordinates().second + memerio.get_height_width().first 
                    < movables[i].get_coordinates().second + movables[i].get_height_width().first * 0.5) {
                        delete_obj(movables, movables_number, i);
                        i--;
                        score += 50;
                        continue;
                    } else 
                        player_died(level, bricks, bricks_number, movables, movables_number, score, max_level, memerio);
            }

            if(movables[i].get_object_type() == obj_types::money) {
                delete_obj(movables, movables_number, i);
                i--;
                score += 100;
                continue;
            }
        }
    }
}

void player_died(int level, Object* &bricks, int &bricks_number, 
    Object* &movables, int &movables_number, int &score, int &max_level, Object &memerio) {
    system("color 4F");
    Sleep(500);
    create_level(level, bricks, bricks_number, movables, movables_number, score, max_level, memerio);
}

void vert_move_object(Object *obj, Object* &bricks, Object* &movables, 
    int &bricks_number, int &movables_number, int &score, int &level, int &max_level, Object &memerio) {
    obj->set_air_state(true);
    obj->change_vertical_speed(0.05);
    obj->set_object_pos(obj->get_coordinates().first, obj->get_coordinates().second + obj->get_vert_horiz_speeds().first);

    for(int i = 0; i < bricks_number; i++ ) {    
        if(is_collision(*obj, bricks[i] ) ) {
            if(obj->get_vert_horiz_speeds().first > 0)
                obj->set_air_state(false);

            if(bricks[i].get_object_type() == obj_types::question_brick && obj->get_vert_horiz_speeds().first < 0 && obj == &memerio) {
                bricks[i].set_object_type(obj_types::empty_brick);
                (get_new_object(movables, movables_number))->init_object( bricks[i].get_coordinates().first, bricks[i].get_coordinates().second-3, 3, 2, obj_types::money);
                movables[movables_number - 1].set_vert_speed(-0.7);
            }

            obj->set_object_pos(obj->get_coordinates().first, obj->get_coordinates().second - obj->get_vert_horiz_speeds().first);
            obj->change_vertical_speed(0);

            if(bricks[i].get_object_type() == obj_types::win_zone) {
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

void horizon_move_object(Object *obj, Object* &bricks, Object* &movables, 
    int &bricks_number, int &movables_number, int &score, int &level, int &max_level, Object &memerio) {
    obj->move_horizontal(obj->get_vert_horiz_speeds().second);

    for(int i = 0; i < bricks_number; i++) {
        if(is_collision(obj[0], bricks[i])) {
            obj->move_horizontal(-obj->get_vert_horiz_speeds().second);
            obj->set_horiz_speed(-obj->get_vert_horiz_speeds().second);
            return;
        }

    }
    if(obj->get_object_type() == obj_types::enemy) { 
        Object temp = *obj;
        vert_move_object(&temp, bricks, movables, bricks_number, movables_number, score, level, max_level, memerio);
        if(temp.in_air_state() == true) {
            obj->move_horizontal(-obj->get_vert_horiz_speeds().second);
            obj->set_horiz_speed(-obj->get_vert_horiz_speeds().second);
        }
    }
}

void horizontal_move_map(float dx, Object* &bricks, Object* &movables, 
    int bricks_number, int movables_number, Object &memerio) {
    memerio.move_horizontal(-dx);
    for(int i = 0; i < bricks_number; i++) {
        if(is_collision(memerio, bricks[i])) {
            memerio.move_horizontal(dx);
            return;
        }
    }
    memerio.move_horizontal(dx);

    for(int i = 0; i < bricks_number; i++) 
        bricks[i].move_horizontal(dx);
    for(int i = 0; i < movables_number; i++)
        movables[i].move_horizontal(dx);
}

void Map::put_object_on_map(Object obj) {
    int ix = static_cast<int>(round(obj.get_coordinates().first));
    int iy = static_cast<int>(round(obj.get_coordinates().second));
    int i_width = static_cast<int>(round(obj.get_height_width().second));
    int i_height = static_cast<int>(round(obj.get_height_width().first));

    for(int i = ix; i < (ix + i_width); i++) 
        for(int j = iy; j < (iy + i_height); j++)
            if(is_pos_in_map(i, j))
                map[j][i] = obj.get_object_type();
}

// void set_object_pos(Object *obj, float x_pos, float y_pos) {
//     obj->x = x_pos;
//     obj->y = y_pos;
// }

bool Map::is_pos_in_map(int x, int y) {
    return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
}

bool is_collision(Object obj1, Object obj2) {
    return (obj1.get_coordinates().first + obj1.get_height_width().second > obj2.get_coordinates().first 
    && obj1.get_coordinates().first < obj2.get_coordinates().first + obj2.get_height_width().second 
    && obj1.get_coordinates().second + obj1.get_height_width().first > obj2.get_coordinates().second 
    && obj1.get_coordinates().second < obj2.get_coordinates().second + obj2.get_height_width().first); 
}


// void init_object(Object *obj, float x_pos, float y_pos, float o_width, float o_height, char obj_type) {
//     set_object_pos(obj, x_pos, y_pos);
//     obj->width = o_width;
//     obj->height = o_height;
//     obj->vert_speed = 0;
//     obj->object_type = obj_type;
//     obj->horiz_speed = 0.2;
// }

void Object::init_object(float x_pos, float y_pos, float o_width, float o_height, char obj_type) {
    set_object_pos(x_pos, y_pos);
    width = o_width;
    height = o_height;
    vert_speed = 0;
    object_type = obj_type;
    horiz_speed = 0.2;
}

void Object::set_object_pos(float x_pos, float y_pos) {
    x = x_pos;
    y = y_pos;
}


Object *get_new_object(Object* &obj_arr, int &obj_number) {
    obj_number++;
    Object *temp_arr = new Object[obj_number];
    for(int i = 0; i < obj_number-1; i++) {
        temp_arr[i] = obj_arr[i];
    }
    delete[] obj_arr;
    obj_arr = temp_arr;
    return &obj_arr[obj_number-1];
}

void delete_obj(Object* &obj_arr, int &obj_number, int i) {
    obj_number--;
    obj_arr[i] = obj_arr[obj_number];
    Object *temp_arr = new Object[obj_number];
    for(int i = 0; i < obj_number; i++) {
        temp_arr[i] = obj_arr[i];
    }
    delete[] obj_arr;
    obj_arr = temp_arr;
}

void Object::set_air_state(bool state) {
    in_air = state;
}

bool Object::in_air_state() {
    return in_air;
}

std::pair<float, float> Object::get_coordinates() {
    return {x, y};
}

char Object::get_object_type() {
    return object_type;
}

std::pair<float, float> Object::get_height_width() {
    return {height, width};
}

void Object::change_vertical_speed(float dy) {
    if(dy == 0)
        vert_speed = 0;
    else
        vert_speed += dy;

}

void Object::change_horizontal_speed(float dx) {
    if(dx == 0)
        horiz_speed = 0;
    else
        horiz_speed += dx;
}

void Object::set_object_type(char new_type) {
    object_type = new_type;
}

void Object::move_horizontal(float dx) {
    x += dx;
}

void Object::move_vertical(float dy) {
    y += dy;
}

std::pair<float, float> Object::get_vert_horiz_speeds() {
    return {vert_speed, horiz_speed};
}

void Object::set_vert_speed(float vy) {
    vert_speed = vy;
}

void Object::set_horiz_speed(float vx) {
    horiz_speed = vx;
}