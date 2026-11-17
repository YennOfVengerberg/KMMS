#pragma once

#include "runtime.hpp"

namespace biv {
	class OSControlSettings;

	class ConsoleRuntime final : public Runtime {
		public:
			ConsoleRuntime(int map_height, int map_width);
			~ConsoleRuntime() override;

			void initialize() override;
			void process_events() override;
			void reset_keyboard(KeyBoard*) override;
			void render(GameMap*) override;
			void delay(std::chrono::milliseconds) override;
			std::chrono::milliseconds frame_delay() const noexcept override;
			bool should_continue() const noexcept override;

		private:
			OSControlSettings* control_settings;
			std::chrono::milliseconds frame_delay_;
	};
}
