// int main() {
// 	biv::cursor::hide_cursor();
	
// 	biv::Board board(200, 25);
	
// 	biv::Rect *bricks = nullptr;
// 	int bricks_count = 0;
	
// 	biv::Movable *movings = nullptr;
// 	int movings_count = 0;

// 	biv::GameFactory::create_first_level(
// 		bricks, bricks_count, 
// 		movings, movings_count
// 	);
// 	biv::Movable mario = { 39, 10, 3, 3, MARIO };
	
// 	biv::Game game(&mario, bricks, bricks_count, movings, movings_count);
	
// 	const int jump_key = VK_SPACE;
// 	const int exit_key = VK_ESCAPE;
// 	const char left_direction_key = 'A';
// 	const char right_direction_key = 'D';
// 	do {
// 		board.clear();
		
// 		if (mario.is_fly() == false && GetKeyState(jump_key) < 0) {
// 			mario.set_vert_speed(-1);
// 		}
		
// 		if (GetKeyState(left_direction_key) < 0) {
// 			game.move_map_horizontally(1);
// 		}
		
// 		if (GetKeyState(right_direction_key) < 0) {
// 			game.move_map_horizontally(-1);
// 		}
		
// 		if (mario.get_y() > board.get_height()) {
// 			system("color 4F");
// 			Sleep(500);
// 			game.restart_level();
// 		}
		
// 		for (int i = 0; i < bricks_count; i++) {
// 			board.put_obj_on_board(&bricks[i]);
// 		}
		
// 		game.check_mario_collisions();
		
// 		mario.move_vertically();
// 		game.check_mario_vertical_static_collisions();
		
// 		for (int i = 0; i < movings_count; i++) {
// 			movings[i].move_vertically();
			
// 			for (int j = 0; j < bricks_count; j++) {
// 				if (movings[i].has_collision(&bricks[j])) {
// 					if (movings[i].get_vert_speed() > 0) {
// 						movings[i].stop_flying();
// 					}
// 					movings[i].move_vertically(-movings[i].get_vert_speed());
// 					movings[i].set_vert_speed(0);
// 					break;
// 				}
// 			}
			
// 			movings[i].move_horizontally();
// 			game.check_enemy_horizontal_static_collisions(&movings[i]);
			
// 			if (movings[i].get_y() > board.get_height()) {
// 				game.delete_movings(i);
// 				i--;
// 				continue;
// 			}
			
// 			board.put_obj_on_board(&movings[i]);
// 		}

// 		board.put_obj_on_board(&mario);
// 		board.put_score(game.get_score());

// 		biv::cursor::set_cursor_position(0, 0);
// 		board.show();
		
// 		Sleep(10);
// 	} while (GetKeyState(exit_key) >= 0);
	
// 	delete [] bricks;
// 	delete [] movings;
	
// 	return 0;
// }