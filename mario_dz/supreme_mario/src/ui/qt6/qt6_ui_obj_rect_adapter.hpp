#pragma once

#include "qt6_ui_obj.hpp"
#include "rect.hpp"

namespace biv {
	class Qt6UIObjectRectAdapter : virtual public Rect, public Qt6UIObject {
		public:
			Qt6UIObjectRectAdapter() = default;
			Qt6UIObjectRectAdapter(
				const Coord& top_left, int width, int height
			);

			int get_bottom() const noexcept override;
			int get_height() const noexcept override;
			int get_left() const noexcept override;
			int get_right() const noexcept override;
			int get_top() const noexcept override;
			bool is_active() const noexcept override;
	};
}
