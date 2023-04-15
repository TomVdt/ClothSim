QT += widgets opengl
QMAKE_CXXFLAGS += -std=c++17
# CONFIG += sanitizer sanitize_address

TARGET   = app

LIBS += -L../../build -lgeneral

INCLUDEPATH += ../
VPATH += ../include

# Fast
# QMAKE_CXXFLAGS += -O2
# Debug
QMAKE_CXXFLAGS += -g

DESTDIR = ../../bin
OBJECTS_DIR = ../../build
MOC_DIR = ../../build


SOURCES += \
    openglrenderer.cpp \
    window.cpp \
    camera.cpp \
    input.cpp \
    main.cpp

HEADERS += \
    openglrenderer.h \
    window.h \
    input.h \
    camera.h


# Let qmake auto-generate resources.qrc
resources.files = \
    ../shaders/frag.glsl \
    ../shaders/vert.glsl
resources.prefix = /

RESOURCES = resources