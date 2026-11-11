#include "qt6_game_map.hpp"

#include <QCoreApplication>
#include <QDir>
#include <QKeyEvent>
#include <QPainter>
#include <algorithm>

using biv::Qt6GameMap;

Qt6GameMap::Qt6GameMap(int height, int width)
	: QWidget(nullptr), GameMap(height, width) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setFocusPolicy(Qt::StrongFocus);
	setWindowTitle(QStringLiteral("Supreme Mario"));
}

void Qt6GameMap::add_obj(Qt6UIObject* obj) {
	objs.push_back(obj);
}

void Qt6GameMap::clear() noexcept {}

void Qt6GameMap::refresh() noexcept {
	update();
}

void Qt6GameMap::remove_obj(Qt6UIObject* obj) {
	objs.erase(
		std::remove(objs.begin(), objs.end(), obj), objs.end()
	);
}

void Qt6GameMap::remove_objs() {
	objs.clear();
}

void Qt6GameMap::show() const noexcept {
	auto* map = const_cast<Qt6GameMap*>(this);
	map->showFullScreen();
	map->activateWindow();
	map->setFocus();
}

bool Qt6GameMap::is_key_down(int key) const noexcept {
	auto it = keys.find(key);
	return it != keys.end() && it->second;
}

void Qt6GameMap::keyPressEvent(QKeyEvent* event) {
	keys[event->key()] = true;
	event->accept();
}

void Qt6GameMap::keyReleaseEvent(QKeyEvent* event) {
	keys[event->key()] = false;
	event->accept();
}

QPixmap Qt6GameMap::sprite(const char* key) {
	const QString name = QString::fromLatin1(key);
	auto it = sprites.find(name);
	if (it != sprites.end()) {
		return it->second;
	}

	const QString path = QDir(
		QStringLiteral(QT6_SPRITE_DIR)
	).filePath(name + QStringLiteral(".png"));
	QPixmap image(path);
	sprites.emplace(name, image);
	return image;
}

void Qt6GameMap::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.fillRect(rect(), QColor(92, 148, 252));
	const double scale_x = static_cast<double>(QWidget::width()) / GameMap::width;
	const double scale_y = static_cast<double>(QWidget::height()) / GameMap::height;
	painter.fillRect(
		0, static_cast<int>((GameMap::height - 3) * scale_y),
		QWidget::width(), static_cast<int>(3 * scale_y),
		QColor(40, 100, 210)
	);

	for (const Qt6UIObject* obj : objs) {
		if (!obj->is_active()) {
			continue;
		}
		const QRect target(
			static_cast<int>(obj->get_left() * scale_x),
			static_cast<int>(obj->get_top() * scale_y),
			static_cast<int>((obj->get_right() - obj->get_left()) * scale_x),
			static_cast<int>((obj->get_bottom() - obj->get_top()) * scale_y)
		);
		const QPixmap image = sprite(obj->get_sprite_key());
		if (!image.isNull()) {
			painter.drawPixmap(target.topLeft(), image);
		} else {
			painter.fillRect(target, QColor(190, 60, 50));
		}
	}
}