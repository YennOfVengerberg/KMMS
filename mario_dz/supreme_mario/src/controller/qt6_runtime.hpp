#pragma once

#include "runtime.hpp"

class QApplication;

namespace biv {
	class Qt6Runtime final : public Runtime {
		public:
			Qt6Runtime(int argc, char* argv[]);
			~Qt6Runtime() override;

			void initialize() override;
			void process_events() override;
			void reset_keyboard(KeyBoard*) override;
			void render(GameMap*) override;
			void delay(std::chrono::milliseconds) override;
			std::chrono::milliseconds frame_delay() const noexcept override;
			bool should_continue() const noexcept override;

		private:
			QApplication* application;
	};
}
