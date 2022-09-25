QT += core gui widgets network
QT += 3dcore 3drender 3dinput 3dextras

CONFIG += c++17
TEMPLATE = app

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/Global.cpp \
    core/Settings.cpp \
    core/Utils.cpp \
    main.cpp \
    project/Project.cpp \
    project/ProjectSettings.cpp \
    ui/ActionManager.cpp \
    ui/GuiSession.cpp \
    ui/MainWindow.cpp \
    ui/SourceEditor.cpp \
    ui/TopMenu.cpp \
    ui/component/BrowseLineEdit.cpp \
    ui/component/SelectableLabel.cpp \
    ui/dialog/NewProject.cpp \
    ui/dialog/Options.cpp \
    ui/dialog/ProjectSettingsDialog.cpp \
    ui/dialog/StandardDialog.cpp \
    ui/dialog/Workspace.cpp

HEADERS += \
    core/Constants.h \
    core/Global.h \
    core/Settings.h \
    core/Utils.h \
    project/Project.h \
    project/ProjectSettings.h \
    ui/ActionManager.h \
    ui/GuiSession.h \
    ui/MainWindow.h \
    ui/SourceEditor.h \
    ui/TopMenu.h \
    ui/component/BrowseLineEdit.h \
    ui/component/SelectableLabel.h \
    ui/dialog/NewProject.h \
    ui/dialog/Options.h \
    ui/dialog/ProjectSettingsDialog.h \
    ui/dialog/StandardDialog.h \
    ui/dialog/Workspace.h

DISTFILES += \
    ../README.md
