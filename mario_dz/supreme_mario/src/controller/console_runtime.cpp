#include "console_runtime.hpp"

#include <thread>

#include "game_map.hpp"
#include "keyboard.hpp"
#include "os_control_settings.hpp"

#ifdef WINDOWS_CONSOLE
	#include "windows_control_settings.hpp"
#elif defined(LINUX_CONSOLE)
	#include "linux_control_settings.hpp"
#endif

using biv::ConsoleRuntime;

ConsoleRuntime::ConsoleRuntime(int map_height, int map_width)
	: control_settings(nullptr), frame_delay_(0) {
#ifdef WINDOWS_CONSOLE
	control_settings = new biv::WindowsControlSettings();
	frame_delay_ = std::chrono::milliseconds(10);
#elif defined(LINUX_CONSOLE)
	control_settings = new biv::LinuxControlSettings(map_height, map_width);
	frame_delay_ = std::chrono::milliseconds(50);
#endif
}

ConsoleRuntime::~ConsoleRuntime() {
	delete control_settings;
}

void ConsoleRuntime::initialize() {
	control_settings->init();
}

void ConsoleRuntime::process_events() {}

void ConsoleRuntime::reset_keyboard(biv::KeyBoard* keyboard) {
	keyboard->off();
	keyboard->on();
}

void ConsoleRuntime::render(biv::GameMap* game_map) {
	control_settings->set_cursor_start_position();
	game_map->show();
}

void ConsoleRuntime::delay(std::chrono::milliseconds duration) {
	std::this_thread::sleep_for(duration);
}

std::chrono::milliseconds ConsoleRuntime::frame_delay() const noexcept {
	return frame_delay_;
}

bool ConsoleRuntime::should_continue() const noexcept {
	return true;
}
