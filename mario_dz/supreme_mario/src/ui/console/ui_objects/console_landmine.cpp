#include "console_landmine.hpp"

using biv::ConsoleMine;

ConsoleMine::ConsoleMine(const Coord& top_left) : Mine(top_left) {}

char ConsoleMine::get_brush() const noexcept {
	return 'm';
}