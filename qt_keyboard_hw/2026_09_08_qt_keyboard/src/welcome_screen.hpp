#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QPushButton>

#include <cstddef>

namespace biv {
	class WelcomeScreen : public QWidget {
		Q_OBJECT

		public:
			WelcomeScreen(QWidget* parent = nullptr);
			
		signals:
            void show_keyboard_window_signal();
	};
}
