#include <QApplication>
#include <QOpenGLWidget>

#include "openglwidget.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);
    QSurfaceFormat::setDefaultFormat(format);

    OpenGLTest widget(nullptr);
    widget.show();

    return app.exec();
}