#include "game.hpp"

#include <algorithm>

using biv::Game;

Game::Game() {}

void Game::add_collisionable(Collisionable* obj) {
	collisionable_objs.push_back(obj);
}

void Game::add_map_movable(MapMovable* obj) {
	map_movable_objs.push_back(obj);
}

void Game::add_mario(Mario* obj) {
	mario = obj;
}

void Game::add_movable(Movable* obj) {
	movable_objs.push_back(obj);
}

void Game::add_moving_collisionable(MovingCollisionable* obj) {
	moving_collisionable_objs.push_back(obj);
}

void Game::add_static_obj(Rect* obj) {
	static_objs.push_back(obj);
}

void Game::check_horizontally_static_collisions() noexcept {
	auto process_collisions = [this](auto& objects) {
		for (auto* obj: objects) {
			if (!obj->is_active()) {
				continue;
			}
			for (Rect* static_obj: static_objs) {
				if (obj->has_collision(static_obj)) {
					obj->process_horizontal_static_collision(static_obj);
					break;
				}
			}
		}
	};
	process_collisions(collisionable_objs);
	process_collisions(moving_collisionable_objs);
}

void Game::check_mario_collision() {
	auto process_collisions = [this](auto& objects) {
		for (int i = 0; i < objects.size(); i++) {
			auto* obj = objects[i];
			if (!obj->is_active()) {
				continue;
			}
			if (obj->has_collision(mario)) {
				obj->process_mario_collision(mario);
				if (!mario->is_active()) {
					return;
				}
			}
		}
	};
	process_collisions(collisionable_objs);
	if (mario->is_active()) {
		process_collisions(moving_collisionable_objs);
	}
}

bool Game::check_static_collisions(Collisionable* obj) const noexcept {
	for (Rect* static_obj: static_objs) {
		if (obj->has_collision(static_obj)) {
			return true;
		}
	}
	return false;
}

void Game::check_vertically_static_collisions() noexcept {
	if (mario->has_collision(static_objs[static_objs.size() - 1])) {
		is_level_end_ = true;
	}
	
	auto process_collisions = [this](auto& objects) {
		for (auto* obj: objects) {
			if (!obj->is_active()) {
				continue;
			}
			for (Rect* static_obj: static_objs) {
				if (obj->has_collision(static_obj)) {
					obj->process_vertical_static_collision(static_obj);
					break;
				}
			}
		}
	};
	process_collisions(collisionable_objs);
	process_collisions(moving_collisionable_objs);
}

void Game::finish() noexcept {
	is_finished_ = true;
}

bool Game::is_finished() const noexcept {
	return is_finished_;
}

bool Game::is_level_end() const noexcept {
	return is_level_end_;
}

void Game::move_map_left() noexcept {
	for (MapMovable* obj: map_movable_objs) {
		obj->move_map_left();
	}
}

void Game::move_map_right() noexcept {
	for (MapMovable* obj: map_movable_objs) {
		obj->move_map_right();
	}
}

void Game::move_objs_horizontally() noexcept {
	for (Movable* obj: movable_objs) {
		obj->move_horizontally();
	}
	for (MovingCollisionable* obj: moving_collisionable_objs) {
		obj->move_horizontally();
	}
}

void Game::move_objs_vertically() noexcept {
	for (Movable* obj: movable_objs) {
		obj->move_vertically();
	}
	for (MovingCollisionable* obj: moving_collisionable_objs) {
		obj->move_vertically();
	}
}

void Game::remove_collisionable(Collisionable* obj) {
	remove_obj(collisionable_objs, obj);
}

void Game::remove_map_movable(MapMovable* obj) {
	remove_obj(map_movable_objs, obj);
}

void Game::remove_mario() noexcept {
	mario = nullptr;
}

void Game::remove_movable(Movable* obj) {
	remove_obj(movable_objs, obj);
}

void Game::remove_moving_collisionable(MovingCollisionable* obj) {
	remove_obj(moving_collisionable_objs, obj);
}

void Game::remove_objs() {
	collisionable_objs.clear();
	map_movable_objs.clear();
	movable_objs.clear();
	moving_collisionable_objs.clear();
	static_objs.clear();
	remove_mario();
}

void Game::remove_static_obj(Rect* obj) {
	remove_obj(static_objs, obj);
}

void Game::start_level() noexcept {
	is_level_end_ = false;
}

// ----------------------------------------------------------------------------
// 									PRIVATE
// ----------------------------------------------------------------------------
template<class T>
void Game::remove_obj(std::vector<T*>& container, T* obj) {
	container.erase(
		std::remove(
			container.begin(), container.end(), obj
		), 
		container.end()
	);
}


// сделать мины - буква m, лежат вместо верхнего края платформы, при столкновении с ними марио умирает