#include "jumping_enemy.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(const Coord& top_left, const int width, const int height)
	: RectMapMovableAdapter(top_left, width, height), MovingCollisionable() {
	hspeed = 0;
	vspeed = JUMP_SPEED;
}

biv::Rect JumpingEnemy::get_rect() const noexcept {
    return {top_left, width, height};
}

biv::Speed JumpingEnemy::get_speed() const noexcept {
    return {vspeed, hspeed};
}

void JumpingEnemy::move_horizontally() noexcept {}

void JumpingEnemy::move_vertically() noexcept {
	Movable::move_vertically();
}

void JumpingEnemy::process_horizontal_static_collision(Rect*) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void JumpingEnemy::process_mario_collision(Collisionable* mario) noexcept {
    if (mario->get_speed().v > 0 &&
        mario->get_speed().v != V_ACCELERATION) {
        kill();
    } else {
        mario->kill();
    }
}

void JumpingEnemy::process_vertical_static_collision(Rect*) noexcept {
	top_left.y -= vspeed;
	if (vspeed > 0) {
		vspeed = JUMP_SPEED;
	} else if (vspeed < 0) {
		vspeed = V_ACCELERATION;
	}
}