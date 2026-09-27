#include "console_enemy.hpp"

using biv::ConsoleEnemy;

ConsoleEnemy::ConsoleEnemy(const Coord& top_left, const int width, const int height) 
	: Enemy(top_left, width, height) {}

char ConsoleEnemy::get_brush() const noexcept {
	return 'e';
}

biv::ConsoleFlyingEnemy::ConsoleFlyingEnemy(
	const Coord& top_left, const int width, const int height
) : FlyingEnemy(top_left, width, height) {}

char biv::ConsoleFlyingEnemy::get_brush() const noexcept {
	return 'f';
}

biv::ConsoleJumpingEnemy::ConsoleJumpingEnemy(
	const Coord& top_left, const int width, const int height
) : JumpingEnemy(top_left, width, height) {}

char biv::ConsoleJumpingEnemy::get_brush() const noexcept {
	return 'j';
}
