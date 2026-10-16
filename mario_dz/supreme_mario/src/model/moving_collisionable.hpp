#pragma once

#include "movable.hpp"
#include "collisionable.hpp"

namespace biv {
	class MovingCollisionable : public Movable, public Collisionable  {
		private:

		public:
			Movable* get_movable() noexcept override {
				return this;
			}
	};
}