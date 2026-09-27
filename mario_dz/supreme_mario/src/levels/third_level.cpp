#include "third_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

biv::GameLevel* ThirdLevel::get_next() {
	return next;
}

bool ThirdLevel::is_final() const noexcept {
	return true;
}

void ThirdLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);

	ui_factory->create_ship({20, 25}, 35, 2);
	ui_factory->create_ship({55, 20}, 10, 7);
	ui_factory->create_ship({72, 25}, 18, 2);
	ui_factory->create_ship({105, 25}, 22, 2);
	ui_factory->create_ship({127, 20}, 10, 7);
	ui_factory->create_ship({150, 25}, 35, 2);

	ui_factory->create_flying_enemy({82, 10}, 3, 2);
	ui_factory->create_jumping_enemy({158, 23}, 3, 2);
	ui_factory->create_moving_platform({90, 23}, 10, 2, 5);
	ui_factory->create_moving_platform({185, 23}, 10, 2, 10);

	ui_factory->create_ship({205, 20}, 20, 7);
}