#include "moving_platform.hpp"

#include "map_movable.hpp"

using biv::MovingPlatform;

MovingPlatform::MovingPlatform(
	const Coord& top_left, const int width, const int height,
	const int travel_distance
) : Ship(top_left, width, height),
	  left_limit(top_left.x),
	  right_limit(top_left.x + (travel_distance > 0 ? travel_distance : 1)) {}

biv::Rect MovingPlatform::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed MovingPlatform::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void MovingPlatform::move_horizontally() noexcept {
	const float current_x = top_left.x;
	float next_x = current_x + direction * MOVEMENT_SPEED;
	if (next_x < left_limit) {
		direction = 1.0f;
		next_x = left_limit;
	} else if (next_x > right_limit) {
		direction = -1.0f;
		next_x = right_limit;
	}

	hspeed = next_x - current_x;
	top_left.x = next_x;

	if (rider == nullptr) {
		return;
	}
	if (!rider->is_active() || rider->get_speed().v < 0) {
		rider = nullptr;
		return;
	}

	const Rect rider_rect = rider->get_rect();
	const float rider_bottom = rider_rect.get_y() + rider_rect.get_height();
	const bool near_top =
		rider_bottom >= top_left.y - 1.0f && rider_bottom <= top_left.y + 1.0f;
	const bool overlaps_horizontally =
		rider_rect.get_x() + rider_rect.get_right() - rider_rect.get_left() > current_x &&
		rider_rect.get_x() < current_x + width;
	if (!near_top || !overlaps_horizontally) {
		rider = nullptr;
		return;
	}

	rider->move_horizontal_offset(hspeed);
}

void MovingPlatform::move_vertically() noexcept {}

void MovingPlatform::move_map_left() noexcept {
	Ship::move_map_left();
	left_limit -= MapMovable::MAP_STEP;
	right_limit -= MapMovable::MAP_STEP;
	hspeed = 0;
}

void MovingPlatform::move_map_right() noexcept {
	Ship::move_map_right();
	left_limit += MapMovable::MAP_STEP;
	right_limit += MapMovable::MAP_STEP;
	hspeed = 0;
}

void MovingPlatform::process_horizontal_static_collision(Rect*) noexcept {}

void MovingPlatform::process_mario_collision(Collisionable* obj) noexcept {
	Mario* mario = dynamic_cast<Mario*>(obj);
	if (mario == nullptr) {
		return;
	}
	if (mario->get_speed().v < 0) {
		if (rider == mario) {
			rider = nullptr;
		}
		return;
	}

	const Rect mario_rect = mario->get_rect();
	const float mario_bottom = mario_rect.get_y() + mario_rect.get_height();
	const bool near_top =
		mario_bottom >= top_left.y - 1.0f && mario_bottom <= top_left.y + 1.0f;
	if (near_top) {
		rider = mario;
	}
}

void MovingPlatform::process_vertical_static_collision(Rect*) noexcept {}