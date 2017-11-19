QT += core gui widgets sql
QT += 3dcore 3drender 3dinput 3dextras

CONFIG += c++11
TARGET = unitbuilder
TEMPLATE = app
DESTDIR = $$(IRBIS_HOME)/build

INCLUDEPATH += $$(IRBIS_HOME)/irbislib/Source

SOURCES += \
    main.cpp \
    UI/MainWindow.cpp

FORMS += \
    UI/MainWindow.ui

HEADERS += \
    UI/MainWindow.h \
    Core/Defines.h

DISTFILES += \
    ../README.md \
    ../.gitignore
