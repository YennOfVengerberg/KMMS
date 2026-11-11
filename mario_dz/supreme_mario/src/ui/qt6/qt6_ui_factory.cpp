#include "qt6_ui_factory.hpp"

#include "box.hpp"
#include "enemy.hpp"
#include "flying_enemy.hpp"
#include "full_box.hpp"
#include "jumping_enemy.hpp"
#include "landmine.hpp"
#include "mario.hpp"
#include "money.hpp"
#include "moving_platform.hpp"
#include "ship.hpp"
#include "qt6_ui_obj_rect_adapter.hpp"
#include <utility>

namespace biv {
	template<class Model>
	class Qt6ModelObject : public Model, public Qt6UIObjectRectAdapter {
		public:
			Qt6ModelObject(const Coord& pos, int width, int height)
				: Model(pos, width, height), Qt6UIObjectRectAdapter(pos, width, height) {}
			const char* get_sprite_key() const noexcept override { return key; }
			static constexpr const char* key = "object";
	};

	class Qt6Box : public Qt6ModelObject<Box> {
		public: using Qt6ModelObject::Qt6ModelObject;
		static constexpr const char* key = "box";
		const char* get_sprite_key() const noexcept override { return key; }
	};
	class Qt6FullBox : public FullBox, public Qt6UIObjectRectAdapter {
		public:
			Qt6FullBox(const Coord& pos, int width, int height, UIFactory* factory)
				: FullBox(pos, width, height, factory),
				  Qt6UIObjectRectAdapter(pos, width, height) {}
		static constexpr const char* key = "full_box";
		const char* get_sprite_key() const noexcept override {
			return FullBox::is_active() ? key : "box";
		}
		bool is_active() const noexcept override { return true; }
	};
	class Qt6Enemy : public Qt6ModelObject<Enemy> {
		public: using Qt6ModelObject::Qt6ModelObject;
		static constexpr const char* key = "enemy";
		const char* get_sprite_key() const noexcept override { return key; }
		bool is_active() const noexcept override { return Enemy::is_active(); }
	};
	class Qt6FlyingEnemy : public Qt6ModelObject<FlyingEnemy> {
		public: using Qt6ModelObject::Qt6ModelObject;
		static constexpr const char* key = "flying_enemy";
		const char* get_sprite_key() const noexcept override { return key; }
		bool is_active() const noexcept override { return FlyingEnemy::is_active(); }
	};
	class Qt6JumpingEnemy : public Qt6ModelObject<JumpingEnemy> {
		public: using Qt6ModelObject::Qt6ModelObject;
		static constexpr const char* key = "jumping_enemy";
		const char* get_sprite_key() const noexcept override { return key; }
		bool is_active() const noexcept override { return JumpingEnemy::is_active(); }
	};
	class Qt6Mario : public Qt6ModelObject<Mario> {
		public: using Qt6ModelObject::Qt6ModelObject;
		static constexpr const char* key = "mario";
		const char* get_sprite_key() const noexcept override { return key; }
		bool is_active() const noexcept override { return Mario::is_active(); }
	};
	class Qt6Mine : public Mine, public Qt6UIObjectRectAdapter {
		public: explicit Qt6Mine(const Coord& pos)
			: Mine(pos), Qt6UIObjectRectAdapter(pos, Mine::WIDTH, Mine::HEIGHT) {}
		static constexpr const char* key = "landmine";
		const char* get_sprite_key() const noexcept override { return key; }
		bool is_active() const noexcept override { return Mine::is_active(); }
	};
	class Qt6Money : public Qt6ModelObject<Money> {
		public: using Qt6ModelObject::Qt6ModelObject;
		static constexpr const char* key = "money";
		const char* get_sprite_key() const noexcept override { return key; }
	};
	class Qt6Platform : public MovingPlatform, public Qt6UIObjectRectAdapter {
		public:
			Qt6Platform(const Coord& pos, int width, int height, int distance)
				: MovingPlatform(pos, width, height, distance),
				  Qt6UIObjectRectAdapter(pos, width, height) {}
			static constexpr const char* key = "moving_platform";
			const char* get_sprite_key() const noexcept override { return key; }
			bool is_active() const noexcept override { return true; }
	};
	class Qt6Ship : public Qt6ModelObject<Ship> {
		public: using Qt6ModelObject::Qt6ModelObject;
		static constexpr const char* key = "ship";
		const char* get_sprite_key() const noexcept override { return key; }
	};

	Qt6UIFactory::Qt6UIFactory(Game* game) : UIFactory(game) {}

	Qt6UIFactory::~Qt6UIFactory() {
		clear_data();
		delete game_map;
	}

	void Qt6UIFactory::clear_data() {
		game->remove_objs();
		if (game_map != nullptr) {
			game_map->remove_objs();
		}
		for (Qt6UIObject* object : objects) {
			delete object;
		}
		objects.clear();
		mario = nullptr;
	}

	template<class T, class... Args>
	T* Qt6UIFactory::create(Args&&... args) {
		T* object = new T(std::forward<Args>(args)...);
		objects.push_back(object);
		game_map->add_obj(object);
		return object;
	}

	void Qt6UIFactory::create_box(const Coord& p, int w, int h) {
		auto* obj = create<Qt6Box>(p, w, h);
		game->add_map_movable(obj); game->add_static_obj(obj);
	}
	void Qt6UIFactory::create_enemy(const Coord& p, int w, int h) {
		auto* obj = create<Qt6Enemy>(p, w, h);
		game->add_map_movable(obj); game->add_movable(obj); game->add_collisionable(obj);
	}
	void Qt6UIFactory::create_flying_enemy(const Coord& p, int w, int h) {
		auto* obj = create<Qt6FlyingEnemy>(p, w, h);
		game->add_map_movable(obj); game->add_moving_collisionable(obj);
	}
	void Qt6UIFactory::create_full_box(const Coord& p, int w, int h) {
		auto* obj = create<Qt6FullBox>(p, w, h, this);
		game->add_map_movable(obj); game->add_static_obj(obj); game->add_collisionable(obj);
	}
	void Qt6UIFactory::create_jumping_enemy(const Coord& p, int w, int h) {
		auto* obj = create<Qt6JumpingEnemy>(p, w, h);
		game->add_map_movable(obj); game->add_moving_collisionable(obj);
	}
	void Qt6UIFactory::create_mario(const Coord& p, int w, int h) {
		if (mario != nullptr) {
			game->remove_collisionable(mario); game->remove_movable(mario);
			game->remove_mario(); game_map->remove_obj(dynamic_cast<Qt6UIObject*>(mario));
		}
		auto* obj = create<Qt6Mario>(p, w, h);
		mario = obj; game->add_collisionable(obj); game->add_movable(obj); game->add_mario(obj);
	}
	void Qt6UIFactory::create_mine(const Coord& p) {
		auto* obj = create<Qt6Mine>(p);
		game->add_map_movable(obj); game->add_collisionable(obj);
	}
	void Qt6UIFactory::create_money(const Coord& p, int w, int h) {
		auto* obj = create<Qt6Money>(p, w, h);
		game->add_map_movable(obj); game->add_movable(obj); game->add_collisionable(obj);
	}
	void Qt6UIFactory::create_moving_platform(const Coord& p, int w, int h, int distance) {
		auto* obj = create<Qt6Platform>(p, w, h, distance);
		game->add_map_movable(obj); game->add_moving_collisionable(obj); game->add_static_obj(obj);
	}
	void Qt6UIFactory::create_ship(const Coord& p, int w, int h) {
		auto* obj = create<Qt6Ship>(p, w, h);
		game->add_map_movable(obj); game->add_static_obj(obj);
	}
	GameMap* Qt6UIFactory::get_game_map(int h, int w) {
		if (game_map == nullptr) game_map = new Qt6GameMap(h, w);
		return game_map;
	}
	Mario* Qt6UIFactory::get_mario() { return mario; }
}