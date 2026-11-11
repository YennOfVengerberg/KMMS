#pragma once

#include "keyboard.hpp"

namespace biv {
	class Qt6GameMap;

	class Qt6KeyBoard final : public KeyBoard {
		public:
			explicit Qt6KeyBoard(const Qt6GameMap* game_map);
			UserInput get_user_input() override;
			void off() override;
			void on() override;

		private:
			const Qt6GameMap* game_map;
	};
}
