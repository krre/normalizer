QT += opengl qml quick

CONFIG += c++11
TEMPLATE = app

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/base/core.cpp \
    src/cpp/base/settings.cpp \
    src/cpp/base/projectfilesystemmodel.cpp \
    src/cpp/base/operatormodel.cpp \
    src/cpp/base/operatorproxymodel.cpp

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
    src/qml/main/About.qml \
    src/qml/components/WindowDialog.qml \
    src/qml/components/ButtonBase.qml \
    src/qml/main/Options.qml \
    src/qml/components/BrowseButton.qml \
    src/qml/components/filedialog/FileDialogBase.qml \
    src/qml/components/filedialog/FileDialogDirectory.qml \
    src/qml/components/filedialog/FileDialogOpen.qml \
    src/js/dialog.js \
    src/qml/main/NewProject.qml \
    src/qml/main/ProjectTreeView.qml \
    src/qml/main/Editor3D.qml \
    src/qml/main/EditorText.qml \
    src/qml/main/Finder.qml \
    src/js/operators.js \
    src/js/object-factory.js \
    src/qml/main/NewSprout.qml \
    src/qml/components/filedialog/FileDialogSave.qml \
    src/js/webgl/scene.js \
    src/js/webgl/gl.js

HEADERS += \
    src/cpp/base/core.h \
    src/cpp/base/settings.h \
    src/cpp/base/projectfilesystemmodel.h \
    src/cpp/base/operatormodel.h \
    src/cpp/base/operatorproxymodel.h
