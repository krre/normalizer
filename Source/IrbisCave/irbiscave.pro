QT += core gui widgets
QT += 3dcore 3drender 3dinput 3dextras

CONFIG += c++11
TARGET = irbiscave
TEMPLATE = app

SOURCES += \
        main.cpp \
        UI/MainWindow.cpp \
    UI/Cave.cpp \
    Db/DatabaseManager.cpp

HEADERS += \
        UI/MainWindow.h \
        Core/Defines.h \
    UI/Cave.h \
    Db/DatabaseManager.h

FORMS += \
        UI/MainWindow.ui
