#include <QApplication>
#include "gui/AppController.h"
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Ehtimam");
    AppController controller;
    controller.start();
    return app.exec();
}
