#pragma once

#include <chrono>
#include <memory>

namespace biv {
	class GameMap;
	class KeyBoard;

	class Runtime {
		public:
			virtual ~Runtime() = default;

			virtual void initialize() = 0;
			virtual void process_events() = 0;
			virtual void reset_keyboard(KeyBoard*) = 0;
			virtual void render(GameMap*) = 0;
			virtual void delay(std::chrono::milliseconds) = 0;
			virtual std::chrono::milliseconds frame_delay() const noexcept = 0;
			virtual bool should_continue() const noexcept = 0;
	};

	std::unique_ptr<Runtime> create_runtime(
		int argc, char* argv[], int map_height, int map_width
	);
}
