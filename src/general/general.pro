TEMPLATE = lib

CONFIG += staticlib
QMAKE_CXXFLAGS += -std=c++17

OBJECTS_DIR += ../../build
MOC_DIR += ../../build
DESTDIR = ../../build
VPATH += ../include

INCLUDEPATH += ..

SOURCES += \
	vector3D.cpp \
	masse.cpp \
	spring.cpp \
	integrator.cpp \
	cloth.cpp \
	system.cpp \
	util.cpp

HEADERS += \
	vector3D.h \
	masse.h \
	spring.h \
	integrator.h \
	cloth.h \
	system.h \
	util.h \
	constants.h \
	drawable.h \
	exceptions.h \
	renderer.h