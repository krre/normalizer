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
    norm/Module.cpp \
    norm/Token.cpp \
    norm/expression/Expression.cpp \
    norm/expression/operator/Math.cpp \
    norm/expression/operator/Operator.cpp \
    norm/function/Function.cpp \
    norm/function/Parameter.cpp \
    norm/helper/ExpressionId.cpp \
    norm/helper/FunctionId.cpp \
    norm/helper/Helper.cpp \
    norm/helper/ModuleId.cpp \
    norm/helper/Name.cpp \
    norm/helper/TypeId.cpp \
    norm/project/Project.cpp \
    norm/project/Version.cpp \
    norm/type/Type.cpp \
    project/Database.cpp \
    project/ProjectManager.cpp \
    project/ProjectSettings.cpp \
    project/ProjectTemplate.cpp \
    project/TokenFactory.cpp \
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
    core/CommonTypes.h \
    core/Constants.h \
    core/Global.h \
    core/Settings.h \
    core/Utils.h \
    core/Version.h \
    norm/Module.h \
    norm/Token.h \
    norm/expression/Expression.h \
    norm/expression/Literal.h \
    norm/expression/operator/Math.h \
    norm/expression/operator/Operator.h \
    norm/function/Function.h \
    norm/function/Parameter.h \
    norm/helper/ExpressionId.h \
    norm/helper/FunctionId.h \
    norm/helper/Helper.h \
    norm/helper/ModuleId.h \
    norm/helper/Name.h \
    norm/helper/TypeId.h \
    norm/project/Project.h \
    norm/project/Version.h \
    norm/type/Type.h \
    project/Database.h \
    project/ProjectManager.h \
    project/ProjectSettings.h \
    project/ProjectTemplate.h \
    project/TokenFactory.h \
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
