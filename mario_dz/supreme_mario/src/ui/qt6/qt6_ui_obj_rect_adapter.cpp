#include "qt6_ui_obj_rect_adapter.hpp"

using biv::Qt6UIObjectRectAdapter;

Qt6UIObjectRectAdapter::Qt6UIObjectRectAdapter(
	const Coord& top_left, int width, int height
) {
	this->top_left = top_left;
	this->width = width;
	this->height = height;
}

int Qt6UIObjectRectAdapter::get_bottom() const noexcept {
	return Rect::get_bottom();
}

int Qt6UIObjectRectAdapter::get_height() const noexcept {
	return Rect::get_height();
}

int Qt6UIObjectRectAdapter::get_left() const noexcept {
	return Rect::get_left();
}

int Qt6UIObjectRectAdapter::get_right() const noexcept {
	return Rect::get_right();
}

int Qt6UIObjectRectAdapter::get_top() const noexcept {
	return Rect::get_top();
}

bool Qt6UIObjectRectAdapter::is_active() const noexcept {
	return true;
}
