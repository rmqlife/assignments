#-------------------------------------------------
#
# Project created by QtCreator 2011-09-02T23:17:26
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = helloGL
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    Vec3f.cpp \
    SimpleObject.cpp \
    gvect.cpp \
    gpoint.cpp \
    triangle.cpp

HEADERS  += mainwidget.h \
    Vec3f.h \
    SimpleObject.h \
    gvect.h \
    gpoint.h \
    triangle.h

FORMS    += mainwidget.ui
