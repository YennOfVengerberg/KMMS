#include "landmine.hpp"

using biv::Mine;

Mine::Mine(const Coord& top_left)
	: RectMapMovableAdapter(top_left, WIDTH, HEIGHT) {}

void Mine::process_mario_collision(Collisionable* mario) noexcept {
	mario->kill();
}