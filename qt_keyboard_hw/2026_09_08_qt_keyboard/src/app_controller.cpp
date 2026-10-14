#include "app_controller.hpp"

#include "keyboard_window.hpp"
#include "welcome_screen.hpp"

biv::AppController::AppController(QObject* parent) : QObject(parent) {
    welcome_screen = std::make_unique<WelcomeScreen>();
    keyboard_window = std::make_unique<KeyBoardWindow>();

    connect(welcome_screen.get(), &WelcomeScreen::show_keyboard_window_signal, this,
            &AppController::show_keyboard_window);
    welcome_screen->show();
}

biv::AppController::~AppController() = default;

void biv::AppController::show_keyboard_window() {
    welcome_screen->hide();
    keyboard_window->show_keyboard_window();
}