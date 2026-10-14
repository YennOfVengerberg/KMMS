#pragma once

#include <QObject>

#include <memory>

namespace biv {
	class KeyBoardWindow;
	class WelcomeScreen;

	class AppController : public QObject {
		Q_OBJECT

		private:
			std::unique_ptr<WelcomeScreen> welcome_screen;
			std::unique_ptr<KeyBoardWindow> keyboard_window;

		public:
			explicit AppController(QObject* parent = nullptr);
			~AppController() override;
			
		private slots:
            void show_keyboard_window();
	};
}
