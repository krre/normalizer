QT += opengl qml quick sql

CONFIG += c++11
TEMPLATE = app

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/base/core.cpp \
    src/cpp/base/settings.cpp \
    src/cpp/base/operatormodel.cpp \
    src/cpp/base/operatorproxymodel.cpp \
    src/cpp/base/filesystemmodel.cpp \
    src/cpp/db/sproutdb.cpp

RESOURCES += \
    src/qml.qrc \
    src/js.qrc

DISTFILES += \
    README.md \
    src/js/utils.js \
    src/qml/main.qml \
    src/qml/main/MainMenu.qml \
    src/js/style.js \
    src/qml/components/MessageDialogBase.qml \
    src/qml/components/WindowDialog.qml \
    src/qml/components/ButtonBase.qml \
    src/qml/components/BrowseButton.qml \
    src/qml/components/filedialog/FileDialogBase.qml \
    src/qml/components/filedialog/FileDialogDirectory.qml \
    src/qml/components/filedialog/FileDialogOpen.qml \
    src/js/dialog.js \
    src/qml/main/Editor3D.qml \
    src/qml/main/Finder.qml \
    src/js/operators.js \
    src/js/object-factory.js \
    src/qml/components/filedialog/FileDialogSave.qml \
    src/js/webgl/scene.js \
    src/js/webgl/gl.js \
    src/qml/main/Workspace.qml \
    src/qml/windows/NewSprout.qml \
    src/qml/windows/Options.qml \
    src/qml/windows/SelectWorkspace.qml \
    src/qml/windows/About.qml \
    src/qml/windows/Rename.qml \
    src/qml/components/Panel.qml

HEADERS += \
    src/cpp/base/core.h \
    src/cpp/base/settings.h \
    src/cpp/base/operatormodel.h \
    src/cpp/base/operatorproxymodel.h \
    src/cpp/base/filesystemmodel.h \
    src/cpp/db/sproutdb.h
