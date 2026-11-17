#include "qt6_runtime.hpp"

#include <QApplication>
#include <thread>

#include "game_map.hpp"

using biv::Qt6Runtime;

Qt6Runtime::Qt6Runtime(int argc, char* argv[])
	: application(new QApplication(argc, argv)) {}

Qt6Runtime::~Qt6Runtime() {
	delete application;
}

void Qt6Runtime::initialize() {}

void Qt6Runtime::process_events() {
	application->processEvents();
}

void Qt6Runtime::reset_keyboard(biv::KeyBoard*) {}

void Qt6Runtime::render(biv::GameMap* game_map) {
	game_map->show();
}

void Qt6Runtime::delay(std::chrono::milliseconds duration) {
	std::this_thread::sleep_for(duration);
}

std::chrono::milliseconds Qt6Runtime::frame_delay() const noexcept {
	return std::chrono::milliseconds(16);
}

bool Qt6Runtime::should_continue() const noexcept {
	return application->applicationState() != Qt::ApplicationInactive;
}
