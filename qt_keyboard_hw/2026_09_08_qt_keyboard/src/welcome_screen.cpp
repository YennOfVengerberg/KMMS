#include "welcome_screen.hpp"

#include <QPushButton>
#include <QVBoxLayout>

biv::WelcomeScreen::WelcomeScreen(QWidget* parent) : QWidget{parent} {
    setWindowTitle("Добро пожаловать в Грустную Клавиатуру");
    resize(500, 300);

    auto* keyboard_button = new QPushButton("Открыть клавиатуру", this);
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(keyboard_button);

    connect(keyboard_button,
            &QPushButton::clicked,
            this,
            &WelcomeScreen::show_keyboard_window_signal);
}
