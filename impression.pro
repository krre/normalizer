QT += opengl qml quick

CONFIG += c++11
TEMPLATE = app

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/base/core.cpp \
    src/cpp/base/settings.cpp \
    src/cpp/base/projectfilesystemmodel.cpp

RESOURCES += \
    src/qml.qrc \
    src/js.qrc

DISTFILES += \
    README.md \
    src/js/utils.js \
    src/qml/main.qml \
    src/qml/main/MainMenu.qml \
    src/js/gl.js \
    src/js/style.js \
    src/js/scene.js \
    src/qml/components/MessageDialogBase.qml \
    src/qml/main/About.qml \
    src/qml/main/WorkArea.qml \
    src/qml/components/WindowDialog.qml \
    src/qml/components/ButtonBase.qml \
    src/qml/main/Options.qml \
    src/qml/components/BrowseButton.qml \
    src/qml/components/filedialog/FileDialogBase.qml \
    src/qml/components/filedialog/FileDialogDirectory.qml \
    src/qml/components/filedialog/FileDialogOpen.qml \
    src/js/dialog.js \
    src/qml/main/NewProject.qml \
    src/qml/main/NewFile.qml \
    src/qml/main/ProjectTreeView.qml

HEADERS += \
    src/cpp/base/core.h \
    src/cpp/base/settings.h \
    src/cpp/base/projectfilesystemmodel.h
