#pragma once

#include <vector>

#include "qt6_game_map.hpp"
#include "ui_factory.hpp"

namespace biv {
	class Qt6UIFactory final : public UIFactory {
		public:
			explicit Qt6UIFactory(Game* game);
			~Qt6UIFactory();

			void clear_data() override;
			void create_box(const Coord&, int, int) override;
			void create_enemy(const Coord&, int, int) override;
			void create_flying_enemy(const Coord&, int, int) override;
			void create_full_box(const Coord&, int, int) override;
			void create_jumping_enemy(const Coord&, int, int) override;
			void create_mario(const Coord&, int, int) override;
			void create_mine(const Coord&) override;
			void create_money(const Coord&, int, int) override;
			void create_moving_platform(const Coord&, int, int, int) override;
			void create_ship(const Coord&, int, int) override;
			GameMap* get_game_map(int, int) override;
			Mario* get_mario() override;

		private:
			template<class T, class... Args>
			T* create(Args&&... args);

			Qt6GameMap* game_map = nullptr;
			Mario* mario = nullptr;
			std::vector<Qt6UIObject*> objects;
	};
}