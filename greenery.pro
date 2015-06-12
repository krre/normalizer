QT += core gui widgets
CONFIG += c++11
TEMPLATE = app

win32 {
    release: DESTDIR = $$OUT_PWD
    debug:   DESTDIR = $$OUT_PWD
}

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp

DISTFILES += \
    README.md

HEADERS += \
    src/mainwindow.h

