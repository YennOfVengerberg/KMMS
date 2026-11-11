#pragma once

#include <QPixmap>
#include <QWidget>
#include <unordered_map>
#include <vector>

#include "game_map.hpp"
#include "qt6_ui_obj.hpp"

namespace biv {
	class Qt6GameMap final : public QWidget, public GameMap {
		public:
			Qt6GameMap(int height, int width);

			void add_obj(Qt6UIObject* obj);
			void clear() noexcept override;
			void refresh() noexcept override;
			void remove_obj(Qt6UIObject* obj);
			void remove_objs() override;
			void show() const noexcept override;
			bool is_key_down(int key) const noexcept;

		protected:
			void keyPressEvent(QKeyEvent* event) override;
			void keyReleaseEvent(QKeyEvent* event) override;
			void paintEvent(QPaintEvent* event) override;

		private:
			QPixmap sprite(const char* key);

			std::vector<Qt6UIObject*> objs;
			std::unordered_map<int, bool> keys;
			std::unordered_map<QString, QPixmap> sprites;
	};
}