QT += core gui widgets network

CONFIG += c++17
TEMPLATE = app

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    ui/MainWindow.cpp

HEADERS += \
    core/Constants.h \
    ui/MainWindow.h

DISTFILES += \
    ../README.md
