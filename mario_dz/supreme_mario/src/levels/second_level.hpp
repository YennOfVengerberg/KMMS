#pragma once

#include "game_level.hpp"

namespace biv {
	class SecondLevel : public GameLevel {
		public:
			SecondLevel(UIFactory* ui_factory);
			
			GameLevel* get_next() override;
			
		private:
			void init_data() override;
	};
}
