QT += core gui widgets network

CONFIG += c++17
TEMPLATE = app

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=../../norm-common/src

LIBS += -L../../norm-common/lib -lnorm-common

unix: PRE_TARGETDEPS += $$PWD/../../norm-common/lib/libnorm-common.a

SOURCES += \
    core/Global.cpp \
    core/Settings.cpp \
    main.cpp \
    ui/MainWindow.cpp \
    ui/SourceEditor.cpp \
    ui/component/BrowseLineEdit.cpp \
    ui/dialog/NewProject.cpp \
    ui/dialog/Options.cpp \
    ui/dialog/StandardDialog.cpp \
    ui/dialog/Workspace.cpp

HEADERS += \
    core/Constants.h \
    core/Global.h \
    core/Settings.h \
    ui/MainWindow.h \
    ui/SourceEditor.h \
    ui/component/BrowseLineEdit.h \
    ui/dialog/NewProject.h \
    ui/dialog/Options.h \
    ui/dialog/StandardDialog.h \
    ui/dialog/Workspace.h

DISTFILES += \
    ../README.md
