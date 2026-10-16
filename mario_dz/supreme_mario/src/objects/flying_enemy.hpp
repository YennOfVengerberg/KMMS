#pragma once

#include "rect_map_movable_adapter.hpp"
#include "moving_collisionable.hpp"

namespace biv {
	class FlyingEnemy : public RectMapMovableAdapter, public MovingCollisionable /* убрать класс enemy, разбить его на абстракции*/ {
		private:
			static constexpr float HORIZONTAL_RANGE = 8.0f;
			static constexpr float VERTICAL_RANGE = 4.0f;
			static constexpr float FLIGHT_SPEED = 0.1f;

			float left_limit;
			float right_limit;
			float top_limit;
			float bottom_limit;
			float vertical_direction = 1.0f;

		public:
			FlyingEnemy(const Coord& top_left, const int width, const int height);

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