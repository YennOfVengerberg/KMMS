#include "fourth_level.hpp"

using biv::FourthLevel;

FourthLevel::FourthLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

biv::GameLevel* FourthLevel::get_next() {
	return next;
}

bool FourthLevel::is_final() const noexcept {
	return true;
}

void FourthLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);

	ui_factory->create_ship({20, 25}, 28, 2);
	ui_factory->create_ship({48, 20}, 8, 7);
	ui_factory->create_ship({62, 25}, 7, 2);
	ui_factory->create_ship({77, 20}, 8, 7);
	ui_factory->create_ship({91, 25}, 7, 2);
	ui_factory->create_moving_platform({101, 23}, 8, 2, 12);
	ui_factory->create_ship({119, 25}, 9, 2);
	ui_factory->create_ship({138, 20}, 8, 7);
	ui_factory->create_ship({152, 25}, 7, 2);
	ui_factory->create_moving_platform({164, 23}, 8, 2, 12);
	ui_factory->create_ship({182, 25}, 8, 2);
	ui_factory->create_ship({198, 19}, 8, 8);
	ui_factory->create_moving_platform({207, 23}, 8, 2, 6);

	ui_factory->create_enemy({24, 23}, 3, 2);
	ui_factory->create_flying_enemy({70, 11}, 3, 2);
	ui_factory->create_jumping_enemy({92, 23}, 3, 2);
	ui_factory->create_flying_enemy({145, 10}, 3, 2);
	ui_factory->create_jumping_enemy({153, 23}, 3, 2);
	ui_factory->create_flying_enemy({190, 9}, 3, 2);
	ui_factory->create_jumping_enemy({199, 17}, 3, 2);

	ui_factory->create_ship({217, 20}, 18, 7);
}