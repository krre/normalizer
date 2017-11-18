QT += core gui widgets sql
QT += 3dcore 3drender 3dinput 3dextras

CONFIG += c++11
TARGET = ../../../build/unitbuilder
TEMPLATE = app

SOURCES += \
    main.cpp \
    UI/MainWindow.cpp

FORMS += \
    UI/MainWindow.ui

HEADERS += \
    UI/MainWindow.h
