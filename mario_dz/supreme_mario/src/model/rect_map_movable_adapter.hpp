/**
	- Почему класс Rect наследуется виртуальным образом?

	- Что такое паттерн адаптер?
	- Для чего он применяется здесь?
	- Какую ещё роль выполняет этот класс?
*/

#pragma once

#include "map_movable.hpp"
#include "rect.hpp"

namespace biv {
	class RectMapMovableAdapter : virtual public Rect, public MapMovable {
		public:
			RectMapMovableAdapter(const Coord& top_left, const int width, const int height);
			
			void move_map_left() noexcept override;
			void move_map_right() noexcept override;
	};
}
