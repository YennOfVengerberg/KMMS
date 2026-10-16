#include "flying_enemy.hpp"

#include "map_movable.hpp"

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(
    const Coord& top_left,
    const int width,
    const int height
)
    : RectMapMovableAdapter(top_left, width, height),
      MovingCollisionable(),
      left_limit(top_left.x - HORIZONTAL_RANGE),
      right_limit(top_left.x + HORIZONTAL_RANGE),
      top_limit(top_left.y),
      bottom_limit(top_left.y + VERTICAL_RANGE) {
    vspeed = 0;
    hspeed = 0.2f;
}

biv::Rect FlyingEnemy::get_rect() const noexcept {
    return {top_left, width, height};
}

biv::Speed FlyingEnemy::get_speed() const noexcept {
    return {vspeed, hspeed};
}

void FlyingEnemy::move_horizontally() noexcept {
	float next_x = top_left.x + hspeed;
	if (next_x < left_limit || next_x > right_limit) {
		hspeed = -hspeed;
		next_x = top_left.x + hspeed;
	}
	top_left.x = next_x;
}

void FlyingEnemy::move_vertically() noexcept {
	if (!is_active()) {
		Movable::move_vertically();
		return;
	}

	float next_y = top_left.y + vertical_direction * FLIGHT_SPEED;
	if (next_y < top_limit || next_y > bottom_limit) {
		vertical_direction = -vertical_direction;
		next_y = top_left.y + vertical_direction * FLIGHT_SPEED;
	}
	vspeed = next_y - top_left.y;
	top_left.y = next_y;
}

void FlyingEnemy::move_map_left() noexcept {
	RectMapMovableAdapter::move_map_left();
	left_limit -= MapMovable::MAP_STEP;
	right_limit -= MapMovable::MAP_STEP;
}

void FlyingEnemy::move_map_right() noexcept {
	RectMapMovableAdapter::move_map_right();
	left_limit += MapMovable::MAP_STEP;
	right_limit += MapMovable::MAP_STEP;
}

void FlyingEnemy::process_horizontal_static_collision(Rect*) noexcept {
    hspeed = -hspeed;
    move_horizontally();
}

void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
    const Rect mario_rect = mario->get_rect();
    const Rect enemy_rect = get_rect();
    const Speed mario_speed = mario->get_speed();
    const Speed enemy_speed = get_speed();

    const float mario_prev_left = mario_rect.get_x() - mario_speed.h;
    const float mario_prev_right =
        mario_prev_left + mario_rect.get_right() - mario_rect.get_left();
    const float mario_prev_bottom =
        mario_rect.get_y() + mario_rect.get_height() - mario_speed.v;
    const float enemy_prev_top = enemy_rect.get_y() - enemy_speed.v;

    const bool overlapped_horizontally_before =
        mario_prev_right > enemy_rect.get_left() &&
        mario_prev_left < enemy_rect.get_right();
    const bool stomp_from_top =
        mario_speed.v > enemy_speed.v &&
        overlapped_horizontally_before &&
        mario_prev_bottom <= enemy_prev_top + 0.5f;

    if (stomp_from_top) {
        kill();
        vspeed = JUMP_SPEED;
    } else {
        mario->kill();
    }
}

void FlyingEnemy::process_vertical_static_collision(Rect*) noexcept {}