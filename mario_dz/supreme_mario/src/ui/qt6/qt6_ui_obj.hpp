#pragma once

#include "rect.hpp"

namespace biv {
	class Qt6UIObject {
		public:
			virtual ~Qt6UIObject() = default;
			virtual int get_bottom() const noexcept = 0;
			virtual int get_height() const noexcept = 0;
			virtual int get_left() const noexcept = 0;
			virtual int get_right() const noexcept = 0;
			virtual int get_top() const noexcept = 0;
			virtual const char* get_sprite_key() const noexcept = 0;
			virtual bool is_active() const noexcept = 0;
	};
}