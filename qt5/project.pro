QT += widgets opengl
QMAKE_CXXFLAGS += -std=c++17

# Fast
# QMAKE_CXXFLAGS += -O2
# Debug
# QMAKE_CXXFLAGS += -g

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build

TARGET   = app
TEMPLATE = app

SOURCES += main.cpp \
    openglwidget.cpp

HEADERS += \
    openglwidget.h

RESOURCES += \
    resource.qrc
