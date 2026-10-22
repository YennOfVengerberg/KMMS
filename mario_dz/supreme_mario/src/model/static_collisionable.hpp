#pragma once

#include "collisionable.hpp"
#include "rect.hpp"
#include "speed.hpp"

namespace biv {
	class StaticCollisionable : virtual public Rect, public Collisionable {
		public:
			Rect get_rect() const noexcept override {
				return {top_left, width, height};
			}

			Speed get_speed() const noexcept override {
				return {0, 0};
			}

			void process_horizontal_static_collision(Rect*) noexcept override {}
			void process_vertical_static_collision(Rect*) noexcept override {}
	};
}