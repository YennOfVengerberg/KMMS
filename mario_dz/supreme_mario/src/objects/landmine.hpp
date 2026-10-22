#pragma once

#include "rect_map_movable_adapter.hpp"
#include "static_collisionable.hpp"

namespace biv {
	class Mine : public RectMapMovableAdapter, public StaticCollisionable {
		public:
			static constexpr int WIDTH = 2;
			static constexpr int HEIGHT = 1;

		public:
			Mine(const Coord& top_left);

			void process_mario_collision(Collisionable* mario) noexcept override;
	};
}