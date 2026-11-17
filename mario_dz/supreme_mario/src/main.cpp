/**
	Игровой цикл - это обощённое представление потока событий, происходящих в игре.

	Игровой цикл:
		1. Установка параметров игры
		2. Получение пользовательского ввода
		3. Обновление внутреннего состояния игры
		4. Обновление изображения на экране
		5. Проверка того, не окончена ли игра

		*** Если игра не окончена, то возвращаемся в пункт № 2.

		6. Завершение
		
	- Какие архитектурные принципы применены при реализации игры?
	
	- На основе какого приципа ООП построен алгоритм игры?
	- Какими элементами языка С++ реализуется этот принцип?
	- Приведите примеры кода, отображающие этот прицип.
*/
#include <chrono>
#include <thread>

#include "first_level.hpp"
#include "game.hpp"
#include "game_level.hpp"
#include "game_map.hpp"
#include "keyboard.hpp"
#include "mario.hpp"
#include "runtime.hpp"
#include "ui_factory.hpp"

#ifdef QT6_GUI
	#include "qt6_game_map.hpp"
	#include "qt6_keyboard.hpp"
	#include "qt6_ui_factory.hpp"
#else
	#include "console_ui_factory.hpp"

	#ifdef WINDOWS_CONSOLE
		#include "windows_keyboard.hpp"
	#elif defined(LINUX_CONSOLE)
		#include "linux_keyboard.hpp"
		#include "ncurses.h"
	#endif
#endif

int main(int argc, char* argv[]) {
	using namespace std::chrono_literals;

	const int map_height = 30;
	const int map_width = 120;
	biv::Game game;
	auto runtime = biv::create_runtime(argc, argv, map_height, map_width);
	runtime->initialize();
	biv::KeyBoard* keyboard = nullptr;
	biv::UIFactory* ui_factory = nullptr;
	biv::GameMap* game_map = nullptr;

#ifdef QT6_GUI
	ui_factory = new biv::Qt6UIFactory(&game);
	game_map = ui_factory->get_game_map(map_height, map_width);
	keyboard = new biv::Qt6KeyBoard(
		static_cast<biv::Qt6GameMap*>(game_map)
	);
#else
	#ifdef WINDOWS_CONSOLE
		keyboard = new biv::WindowsKeyBoard();
	#elif defined(LINUX_CONSOLE)
		keyboard = new biv::LinuxKeyboard();
	#endif

	keyboard->on();

	ui_factory = new biv::ConsoleUIFactory(&game);
	game_map = ui_factory->get_game_map(map_height, map_width);
#endif

	biv::GameLevel* game_level = new biv::FirstLevel(ui_factory);
	biv::Mario* mario = ui_factory->get_mario();

	runtime->render(game_map);

	biv::UserInput user_input;
	do {
		runtime->process_events();

		user_input = keyboard->get_user_input();
		switch (user_input) {
			case biv::UserInput::DEBUG_SKIP_LEVEL:
				if (!game_level->is_final()) {
					game_level = game_level->get_next();
					mario = ui_factory->get_mario();

					runtime->delay(500ms);
					runtime->reset_keyboard(keyboard);

					game.start_level();
				}
				break;
			case biv::UserInput::MAP_LEFT:
				mario->move_map_left();
				if (!game.check_static_collisions(mario)) {
					game.move_map_left();
				}
				mario->move_map_right();
				break;
			case biv::UserInput::MAP_RIGHT:
				mario->move_map_right();
				if (!game.check_static_collisions(mario)) {
					game.move_map_right();
				}
				mario->move_map_left();
				break;
			case biv::UserInput::MARIO_JUMP:
				mario->jump();
				break;
			case biv::UserInput::EXIT:
				game.finish();
				break;
			case biv::UserInput::NO_INPUT:
				break;
		}

		game.move_objs_horizontally();
		game.check_horizontally_static_collisions();
		game.move_objs_vertically();
		game.check_mario_collision();
		game.check_vertically_static_collisions();

		if (game_map->is_below_map(mario->get_top()) || !mario->is_active()) {
			runtime->reset_keyboard(keyboard);
			game_level->restart();
			mario = ui_factory->get_mario();
			runtime->delay(1000ms);
		}

		if (game.is_level_end()) {
			if (!game_level->is_final()) {
				game_level = game_level->get_next();
				mario = ui_factory->get_mario();
				runtime->delay(1000ms);
				runtime->reset_keyboard(keyboard);
				game.start_level();
			} else {
				game.finish();
			}
		}

		game_map->refresh();
		runtime->process_events();
		runtime->render(game_map);
		runtime->delay(runtime->frame_delay());
	} while (!game.is_finished() && runtime->should_continue());

	delete game_level;
	return 0;
}
