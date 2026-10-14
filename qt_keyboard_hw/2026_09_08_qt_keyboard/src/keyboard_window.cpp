#include "keyboard_window.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

using biv::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
	const int keyboard_width = 1160;
	resize(keyboard_width, 710);
    setWindowTitle("Весёлая клавиатура!");
	
	QPixmap pixmap("img/grustnii-smail.png");
	QLabel* image = new QLabel(this);
	image->setFixedSize(200, 200);
	image->setPixmap(pixmap);
	image->setScaledContents(true);
	
	QHBoxLayout* smail_layout = new QHBoxLayout();
	smail_layout->addWidget(image);

    display = new QLineEdit();
	display->setMinimumHeight(80);
	display->setFont(QFont("Roboto", 40));
    display->setReadOnly(true);
	display->setFocusPolicy(Qt::NoFocus);
	display->setText("Помоги мне заработать лучше...");

	keyboard = new KeyBoard(keyboard_width);
	keyboard->setFocusPolicy(Qt::NoFocus);
	connect(keyboard,
			&KeyBoard::key_clicked,
			this,
			&KeyBoardWindow::handle_keyboard_click);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);
	setFocusPolicy(Qt::StrongFocus);
}

void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
	if (event->isAutoRepeat()) {
		return;
	}

	switch (event->key()) {
	case Qt::Key_Backspace:
		display->backspace();
		return;
	case Qt::Key_Space:
		append_character(" ");
		return;
	case Qt::Key_CapsLock:
		caps_lock_enabled = !caps_lock_enabled;
		return;
	default:
		break;
	}

	const int key = event->nativeVirtualKey();
	if (keyboard->is_key_allowed(key)) {
		keyboard->animate_button(key);
	}
}

void KeyBoardWindow::show_keyboard_window() {
	show();
	raise();
	activateWindow();
	setFocus();
}

void KeyBoardWindow::handle_keyboard_click(const QString& text) {
	if (text == "Удалить") {
		display->backspace();
		return;
	}

	if (text.isEmpty()) {
		append_character(" ");
		return;
	}

	if (text == "Caps") {
		caps_lock_enabled = !caps_lock_enabled;
		return;
	}

	if (text == "Tab" || text == "Enter" || text == "Shift") {
		return;
	}

	append_character(text);
	setFocus();
}

void KeyBoardWindow::append_character(const QString& text) {
	if (text.size() == 1 && text.front().isLetter()) {
		display->insert(caps_lock_enabled ? text.toUpper() : text.toLower());
		return;
	}

	display->insert(text);
}
