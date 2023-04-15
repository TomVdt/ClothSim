#include <QApplication>
#include <QMainWindow>
#include "include/window.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);

    Window window;
    window.show();

    return app.exec();
}