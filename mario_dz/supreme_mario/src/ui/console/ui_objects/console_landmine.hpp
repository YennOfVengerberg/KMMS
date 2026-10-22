#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "landmine.hpp"

namespace biv {
	class ConsoleMine : public Mine, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleMine(const Coord& top_left);

			char get_brush() const noexcept override;
	};
}