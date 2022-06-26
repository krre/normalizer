QT += core gui widgets network

CONFIG += c++17
TEMPLATE = app

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=../../norm-core/src

SOURCES += \
    core/Global.cpp \
    main.cpp \
    project/Project.cpp \
    ui/MainWindow.cpp \
    ui/SourceEditor.cpp \
    ui/dialog/NewProject.cpp \
    ui/dialog/Options.cpp \
    ui/dialog/StandardDialog.cpp \
    ui/dialog/Workspace.cpp

HEADERS += \
    core/Constants.h \
    core/Global.h \
    project/Project.h \
    ui/MainWindow.h \
    ui/SourceEditor.h \
    ui/dialog/NewProject.h \
    ui/dialog/Options.h \
    ui/dialog/StandardDialog.h \
    ui/dialog/Workspace.h

DISTFILES += \
    ../README.md
