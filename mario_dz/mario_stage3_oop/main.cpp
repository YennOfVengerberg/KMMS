#include "game_logic.hpp"
#include "map_and_displays.hpp"
#include "objects.hpp"
#include "level_creator.hpp"

int main() {
	Map map;
	
	Brick *bricks = nullptr;
	int bricks_number = 0;
	
	Movable *movables = nullptr;
	int movables_number = 0;

	Level_Creator::create_level(1, 
		bricks, bricks_number, 
		movables, movables_number
	);
	
	Mario mario;
    mario.init_object(39, 10, 3, 3, obj_types::player);
	
	Game game(&mario, bricks, bricks_number, movables, movables_number);
	
	do {
		map.clear_map();

		if(mario.in_air_state() == false && GetKeyState(VK_UP) < 0) mario.set_vert_speed(-1.0);
        if(GetKeyState(VK_LEFT) < 0) game.horizontal_move_map(1);
        if(GetKeyState(VK_RIGHT) < 0) game.horizontal_move_map(-1);
		
		// if (mario.in_air_state() == false && GetKeyState(jump_key) < 0) {
		// 	mario.set_vert_speed(-1);
		// }
		
		// if (GetKeyState(left_direction_key) < 0) {
		// 	game.horizontal_move_map(1);
		// }
		
		// if (GetKeyState(right_direction_key) < 0) {
		// 	game.horizontal_move_map(-1);
		// }
		
		// if (mario.get_obj_dimensions().y > MAP_HEIGHT) {
		// 	system("color 4F");
		// 	Sleep(500);
		// 	game.restart_level();
		// }
		
		for (int i = 0; i < bricks_number; i++) {
			map.put_object_on_map(bricks[i]);
		}
		
		//game.player_collision();
		
		game.vert_move_object(&mario);
		game.player_collision();
		
		for (int i = 0; i < movables_number; i++) {
			game.vert_move_object(&movables[i]);
			
			for (int j = 0; j < bricks_number; j++) {
				if (game.is_collision(movables[i], bricks[j])) {
					if (movables[i].get_obj_speeds().vert_speed > 0) {
						movables[i].set_air_state(false);
					}
					movables[i].move_vertical(-movables[i].get_obj_speeds().vert_speed);
					movables[i].set_vert_speed(0);
					break;
				}
			}
			
			game.horizon_move_object(&movables[i]);
			//game.check_enemy_horizontal_static_collisions(&movables[i]);
			
			if (movables[i].get_obj_dimensions().y > MAP_HEIGHT) {
				game.delete_obj(movables, movables_number, i);
				i--;
				continue;
			}
			
			map.put_object_on_map(movables[i]);
		}

		map.put_object_on_map(mario);
		map.display_score(game.get_score());

        map.set_cursor(0, 0);
		map.show_map();
		
		Sleep(10);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	delete [] bricks;
	delete [] movables;
	
	return 0;
}