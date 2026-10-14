#pragma once

#include <cstddef>

#include <QKeyEvent>
#include <QLineEdit>
#include <QWidget>

#include "keyboard.hpp"

namespace biv {
	class KeyBoardWindow : public QWidget {
		private:
			QLineEdit* display;
			KeyBoard* keyboard;
			bool caps_lock_enabled = false;

		public:
			KeyBoardWindow(QWidget* parent = nullptr);
			
		protected:
			void keyPressEvent(QKeyEvent* event) override;

		public slots:
			void show_keyboard_window();

		private slots:
			void handle_keyboard_click(const QString& text);
			void append_character(const QString& text);
	};
}
