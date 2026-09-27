#include "flying_enemy.hpp"

#include "map_movable.hpp"

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(const Coord& top_left, const int width, const int height)
	: Enemy(top_left, width, height),
	  left_limit(top_left.x - HORIZONTAL_RANGE),
	  right_limit(top_left.x + HORIZONTAL_RANGE),
	  top_limit(top_left.y),
	  bottom_limit(top_left.y + VERTICAL_RANGE) {}

void FlyingEnemy::move_horizontally() noexcept {
	float next_x = top_left.x + hspeed;
	if (next_x < left_limit || next_x > right_limit) {
		hspeed = -hspeed;
		next_x = top_left.x + hspeed;
	}
	top_left.x = next_x;
}

void FlyingEnemy::move_vertically() noexcept {
	float next_y = top_left.y + vertical_direction * FLIGHT_SPEED;
	if (next_y < top_limit || next_y > bottom_limit) {
		vertical_direction = -vertical_direction;
		next_y = top_left.y + vertical_direction * FLIGHT_SPEED;
	}
	vspeed = next_y - top_left.y;
	top_left.y = next_y;
}

void FlyingEnemy::move_map_left() noexcept {
	Enemy::move_map_left();
	left_limit -= MapMovable::MAP_STEP;
	right_limit -= MapMovable::MAP_STEP;
}

void FlyingEnemy::move_map_right() noexcept {
	Enemy::move_map_right();
	left_limit += MapMovable::MAP_STEP;
	right_limit += MapMovable::MAP_STEP;
}

void FlyingEnemy::process_vertical_static_collision(Rect*) noexcept {}