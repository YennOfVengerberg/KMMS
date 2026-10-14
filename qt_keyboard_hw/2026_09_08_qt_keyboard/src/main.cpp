#include <QApplication>

#include "app_controller.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    biv::AppController controller;
	
    return app.exec();
}
