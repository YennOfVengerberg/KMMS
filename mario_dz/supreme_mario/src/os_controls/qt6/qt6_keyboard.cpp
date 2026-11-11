#include "qt6_keyboard.hpp"

#include <QKeySequence>

#include "qt6_game_map.hpp"

using biv::Qt6KeyBoard;
using biv::UserInput;

Qt6KeyBoard::Qt6KeyBoard(const biv::Qt6GameMap* game_map)
	: game_map(game_map) {}

UserInput Qt6KeyBoard::get_user_input() {
	if (game_map->is_key_down(Qt::Key_Left)) {
		return UserInput::MAP_RIGHT;
	}
	if (game_map->is_key_down(Qt::Key_Right)) {
		return UserInput::MAP_LEFT;
	}
	if (game_map->is_key_down(Qt::Key_Up)) {
		return UserInput::MARIO_JUMP;
	}
	if (game_map->is_key_down(Qt::Key_Q)) {
		return UserInput::EXIT;
	}
	if (game_map->is_key_down(Qt::Key_Z)) {
		return UserInput::DEBUG_SKIP_LEVEL;
	}
	return UserInput::NO_INPUT;
}

void Qt6KeyBoard::off() {}
void Qt6KeyBoard::on() {}
