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
	const double scale = std::min(
		static_cast<double>(QWidget::width()) / GameMap::width,
		static_cast<double>(QWidget::height()) / GameMap::height
	);
	const double map_width = GameMap::width * scale;
	const double map_height = GameMap::height * scale;
	const double offset_x = (QWidget::width() - map_width) / 2.0;
	const double offset_y = (QWidget::height() - map_height) / 2.0;
	painter.fillRect(
		QRectF(
			offset_x,
			offset_y + (GameMap::height - 3) * scale,
			map_width,
			3 * scale
		),
		QColor(40, 100, 210)
	);

	for (const Qt6UIObject* obj : objs) {
		if (!obj->is_active()) {
			continue;
		}
		const QRect target(
			static_cast<int>(offset_x + obj->get_left() * scale),
			static_cast<int>(offset_y + obj->get_top() * scale),
			static_cast<int>((obj->get_right() - obj->get_left()) * scale),
			static_cast<int>((obj->get_bottom() - obj->get_top()) * scale)
		);
		const QPixmap image = sprite(obj->get_sprite_key());
		if (!image.isNull()) {
			const QString sprite_key = QString::fromLatin1(obj->get_sprite_key());
			const bool is_tiled = sprite_key == QStringLiteral("ship")
				|| sprite_key == QStringLiteral("box")
				|| sprite_key == QStringLiteral("full_box")
				|| sprite_key == QStringLiteral("moving_platform");
			if (is_tiled) {
				const QSize tile_size(
					std::max(1, static_cast<int>(scale)),
					std::max(1, static_cast<int>(scale))
				);
				const QPixmap tile = image.scaled(
					tile_size,
					Qt::IgnoreAspectRatio,
					Qt::FastTransformation
				);
				painter.drawTiledPixmap(target, tile);
			} else {
				const QSize sprite_size(
					std::max(1, static_cast<int>(image.width() * scale / 32.0)),
					std::max(1, static_cast<int>(image.height() * scale / 32.0))
				);
				painter.drawPixmap(
					target.topLeft(),
					image.scaled(
						sprite_size,
						Qt::IgnoreAspectRatio,
						Qt::FastTransformation
					)
				);
			}
		} else {
			painter.fillRect(target, QColor(190, 60, 50));
		}
	}
}