#include "game_logic.hpp"
#include "obj_types.hpp"

Game::Game(Mario *mario, Brick *bricks, int bricks_number, Movable *movables, int movables_number) {
    this->mario = *mario;
    this->bricks = bricks;
    this->bricks_number = bricks_number;
    this->movables = movables;
    this->movables_number = movables_number;
    score = 0;
    level_score = 0;
}

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
                     } //else 
                    //     player_died();
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

                //create_level();
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


//------------

// void Game::player_died() {
//     system("color 4F");
//     Sleep(500);
//     score -= level_score;
//     create_level();
// }
//------------

int Game::get_score() const {
    return score;
}