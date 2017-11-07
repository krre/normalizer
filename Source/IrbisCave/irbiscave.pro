QT += core gui widgets

TARGET = irbiscave
TEMPLATE = app

SOURCES += \
        main.cpp \
        UI/MainWindow.cpp \
    UI/Cave.cpp

HEADERS += \
        UI/MainWindow.h \
        Core/Defines.h \
    UI/Cave.h

FORMS += \
        UI/MainWindow.ui
