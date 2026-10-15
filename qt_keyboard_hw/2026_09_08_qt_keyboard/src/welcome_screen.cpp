#include "welcome_screen.hpp"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

biv::WelcomeScreen::WelcomeScreen(QWidget* parent) : QWidget{parent} {
    setWindowTitle("Грустная клавиатура?..");
    resize(500, 300);

    QPixmap pixmap("img/grustnii-smail.png");
	QLabel* image = new QLabel(this);
	image->setFixedSize(230, 230);
	image->setPixmap(pixmap);
	image->setScaledContents(true);

    auto* keyboard_button = new QPushButton("Начать веселье", this);
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(image);
    layout->addWidget(keyboard_button);

    connect(keyboard_button,
            &QPushButton::clicked,
            this,
            &WelcomeScreen::show_keyboard_window_signal);
}
