#include "jumping_enemy.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(const Coord& top_left, const int width, const int height)
	: Enemy(top_left, width, height) {
	hspeed = 0;
	vspeed = JUMP_SPEED;
}

void JumpingEnemy::move_horizontally() noexcept {}

void JumpingEnemy::move_vertically() noexcept {
	Movable::move_vertically();
}

void JumpingEnemy::process_vertical_static_collision(Rect*) noexcept {
	top_left.y -= vspeed;
	if (vspeed > 0) {
		vspeed = JUMP_SPEED;
	} else if (vspeed < 0) {
		vspeed = V_ACCELERATION;
	}
}