#pragma once

#include "collisionable.hpp"
#include "mario.hpp"
#include "movable.hpp"
#include "ship.hpp"

namespace biv {
	class MovingPlatform : public Ship, public Movable, public Collisionable {
		private:
			static constexpr float MOVEMENT_SPEED = 0.1f;

			float left_limit;
			float right_limit;
			float direction = 1.0f;
			Mario* rider = nullptr;

		public:
			MovingPlatform(
				const Coord& top_left, const int width, const int height,
				const int travel_distance
			);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;
			void move_map_left() noexcept override;
			void move_map_right() noexcept override;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
	};
}