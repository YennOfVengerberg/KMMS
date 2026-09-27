#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "moving_platform.hpp"
#include "ship.hpp"

namespace biv {
	class ConsoleShip : public Ship, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleShip(const Coord& top_left, const int width, const int height);
			
			char get_brush() const noexcept override;
	};

	class ConsoleMovingPlatform : public MovingPlatform, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleMovingPlatform(
				const Coord& top_left, const int width, const int height,
				const int travel_distance
			);

			char get_brush() const noexcept override;
	};
}
