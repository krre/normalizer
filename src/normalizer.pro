QT += core gui widgets network
QT += 3dcore 3drender 3dinput 3dextras

CONFIG += c++17 object_parallel_to_source
TEMPLATE = app

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/Global.cpp \
    core/Settings.cpp \
    core/Utils.cpp \
    main.cpp \
    norm/expression/Expression.cpp \
    norm/expression/operator/Math.cpp \
    norm/expression/operator/Operator.cpp \
    norm/type/Type.cpp \
    norm/unit/Function.cpp \
    norm/unit/Parameter.cpp \
    norm/unit/Unit.cpp \
    norm/unit/helper/Helper.cpp \
    norm/unit/helper/Name.cpp \
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
    ui/dialog/ProjectSettings.cpp \
    ui/dialog/StandardDialog.cpp \
    ui/dialog/Workspace.cpp

HEADERS += \
    core/Constants.h \
    core/Global.h \
    core/Settings.h \
    core/Utils.h \
    norm/expression/Expression.h \
    norm/expression/operator/Math.h \
    norm/expression/operator/Operator.h \
    norm/type/Type.h \
    norm/unit/Function.h \
    norm/unit/Parameter.h \
    norm/unit/Unit.h \
    norm/unit/helper/Helper.h \
    norm/unit/helper/Name.h \
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
    ui/dialog/ProjectSettings.h \
    ui/dialog/StandardDialog.h \
    ui/dialog/Workspace.h

DISTFILES += \
    ../README.md
