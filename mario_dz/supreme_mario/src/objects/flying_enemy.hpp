#pragma once

#include "enemy.hpp"

namespace biv {
	class FlyingEnemy : public Enemy {
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

			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;
			void move_map_left() noexcept override;
			void move_map_right() noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
	};
}