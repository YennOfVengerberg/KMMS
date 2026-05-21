#include "game_logic.hpp"
#include "obj_types.hpp"

template <typename T>
T *Game::get_new_object(T* &obj_arr, int &obj_number) {
    obj_number++;
    T *temp_arr = new T[obj_number];
    for(int i = 0; i < obj_number-1; i++) {
        temp_arr[i] = obj_arr[i];
    }
    delete[] obj_arr;
    obj_arr = temp_arr;
    return &obj_arr[obj_number-1];
}

template <typename T>
void Game::delete_obj(T* &obj_arr, int &obj_number, int i) {
    obj_number--;
    obj_arr[i] = obj_arr[obj_number];
    T *temp_arr = new T[obj_number];
    for(int i = 0; i < obj_number; i++) {
        temp_arr[i] = obj_arr[i];
    }
    delete[] obj_arr;
    obj_arr = temp_arr;
}
//-------

bool Game::is_collision(Object obj1, Object obj2) {
    obj_dimensions obj1_dims = obj1.get_obj_dimensions();
    obj_dimensions obj2_dims = obj2.get_obj_dimensions();

    return (obj1_dims.x + obj1_dims.width > obj2_dims.x 
    && obj1_dims.x < obj2_dims.x + obj2_dims.width 
    && obj1_dims.y + obj1_dims.height > obj2_dims.y 
    && obj1_dims.y < obj2_dims.y + obj2_dims.height
    ); 
}

void Game::player_collision() {
    for(int i = 0; i < movables_number; i++) {
        if(is_collision(mario, movables[i])) {
            if(movables[i].get_object_type() == obj_types::enemy) {
                if(mario.in_air_state() == true && mario.get_obj_speeds().horiz_speed > 0 
                    && mario.get_obj_dimensions().y + mario.get_obj_dimensions().height 
                    < movables[i].get_obj_dimensions().y + movables[i].get_obj_dimensions().height * 0.5) {
                        delete_obj(movables, movables_number, i);
                        i--;
                        level_score += 50;
                        score += 50;
                        continue;
                    } else 
                        player_died();
            }

            if(movables[i].get_object_type() == obj_types::money) {
                delete_obj(movables, movables_number, i);
                i--;
                level_score += 100;
                score += 100;
                continue;
            }
        }
    }
}
//-------

void Game::horizon_move_object(Movable *obj) {
    obj->move_horizontal(obj->get_obj_speeds().horiz_speed);

    for(int i = 0; i < bricks_number; i++) {
        if(is_collision(obj[0], bricks[i])) {
            obj->move_horizontal(-obj->get_obj_speeds().horiz_speed);
            obj->set_horiz_speed(-obj->get_obj_speeds().horiz_speed);
            return;
        }

    }
    if(obj->get_object_type() == obj_types::enemy) { 
        Movable temp = *obj;
        vert_move_object(&temp);
        if(temp.in_air_state() == true) {
            obj->move_horizontal(-obj->get_obj_speeds().horiz_speed);
            obj->set_horiz_speed(-obj->get_obj_speeds().horiz_speed);
        }
    }
}

void Game::vert_move_object(Movable *obj) {
    obj->set_air_state(true);
    obj->change_vertical_speed(0.05);
    obj->set_object_pos(obj->get_obj_dimensions().x, 
        obj->get_obj_dimensions().y + obj->get_obj_speeds().vert_speed);

    for(int i = 0; i < bricks_number; i++ ) {    
        if(is_collision(*obj, bricks[i] ) ) {
            if(obj->get_obj_speeds().vert_speed > 0)
                obj->set_air_state(false);

            if(bricks[i].get_object_type() == obj_types::question_brick && 
            obj->get_obj_speeds().vert_speed < 0 && obj == &mario) {
                bricks[i].set_object_type(obj_types::empty_brick);
                (get_new_object(movables, movables_number))->
                    init_object(bricks[i].get_obj_dimensions().x, bricks[i].get_obj_dimensions().y-3, 3, 2, obj_types::money);
                movables[movables_number - 1].set_vert_speed(-0.7);
            }

            obj->set_object_pos(obj->get_obj_dimensions().x, obj->get_obj_dimensions().y - obj->get_obj_speeds().vert_speed);
            obj->change_vertical_speed(0);

            if(bricks[i].get_object_type() == obj_types::win_zone) {
                current_level++;
                if(current_level > max_level) {
                    std::cout << "w w w w w w w wwin win win w w w w w your score " << score;
                    current_level = 1;
                } 
                system("color 2F");
                Sleep(1000);

                create_level();
            }
            break;
        }
    }
}

void Game::horizontal_move_map(float dx) {
    mario.move_horizontal(-dx);
    for(int i = 0; i < bricks_number; i++) {
        if(is_collision(mario, bricks[i])) {
            mario.move_horizontal(dx);
            return;
        }
    }
    mario.move_horizontal(dx);

    for(int i = 0; i < bricks_number; i++) 
        bricks[i].move_horizontal(dx);
    for(int i = 0; i < movables_number; i++)
        movables[i].move_horizontal(dx);
}
//----------

void Game::create_level() {
    system("color 1F");

    delete[] bricks;
    bricks = nullptr;
    bricks_number = 0;

    delete[] movables;
    movables = nullptr;
    movables_number = 0;

    mario.init_object(39, 10, 3, 3, obj_types::player);
    level_score = 0;

    switch(current_level) {
        case 1:
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
            break;
        }

        case 2: {
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
            break;
        }
        case 3: {
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
            break;

        }
        case 4: {
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
            break;
        }
    }
}
//------------

void Game::player_died() {
    system("color 4F");
    Sleep(500);
    score -= level_score;
    create_level();
}
//------------

void Game::run_game_loop() {
    do  {
        map.clear_map();

        if(mario.in_air_state() == false && GetKeyState(VK_UP) < 0) mario.set_vert_speed(-1.0);
        if(GetKeyState(VK_LEFT) < 0) horizontal_move_map(1);
        if(GetKeyState(VK_RIGHT) < 0) horizontal_move_map(-1);

        if(mario.get_obj_dimensions().y > MAP_HEIGHT) player_died();

        vert_move_object(&mario);
        player_collision();

        for(int i = 0; i < bricks_number; i++) {
            map.put_object_on_map(bricks[i]);
        }
        for(int i = 0; i < movables_number; i++) {
            vert_move_object(movables + i);
            horizon_move_object(movables + i);
            if(movables[i].get_obj_dimensions().y > MAP_HEIGHT) {
                delete_obj(movables, movables_number, i);
                i--;
                continue;
            }
            map.put_object_on_map(movables[i]);
        }

        map.put_object_on_map(mario);
        map.display_score(score);


        map.set_cursor(0, 0);
        map.show_map();

        Sleep(10);
    } while(GetKeyState(VK_ESCAPE) >= 0);
}