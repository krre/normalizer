QT += core gui widgets
CONFIG += c++11
TEMPLATE = app

win32 {
    release: DESTDIR = $$OUT_PWD
    debug:   DESTDIR = $$OUT_PWD
}

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/mainwindow.cpp \
    src/cpp/visualarea.cpp

DISTFILES += \
    README.md

HEADERS += \
    src/cpp/mainwindow.h \
    src/cpp/visualarea.h

