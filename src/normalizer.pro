QT += core gui widgets network

CONFIG += c++17
TEMPLATE = app

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=../../libnorm/src

SOURCES += \
    main.cpp \
    ui/MainWindow.cpp \
    ui/dialog/NewProject.cpp \
    ui/dialog/StandardDialog.cpp

HEADERS += \
    core/Constants.h \
    ui/MainWindow.h \
    ui/dialog/NewProject.h \
    ui/dialog/StandardDialog.h

DISTFILES += \
    ../README.md
