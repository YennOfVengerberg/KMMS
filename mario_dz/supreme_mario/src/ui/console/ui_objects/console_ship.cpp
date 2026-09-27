#include "console_ship.hpp"

using biv::ConsoleShip;

ConsoleShip::ConsoleShip(const Coord& top_left, const int width, const int height) 
	: Ship(top_left, width, height) {}

char ConsoleShip::get_brush() const noexcept {
	return '#';
}

biv::ConsoleMovingPlatform::ConsoleMovingPlatform(
	const Coord& top_left, const int width, const int height,
	const int travel_distance
) : MovingPlatform(top_left, width, height, travel_distance) {}

char biv::ConsoleMovingPlatform::get_brush() const noexcept {
	return '=';
}
