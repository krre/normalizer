QT += qml quick widgets 3dcore 3drenderer 3dinput 3dquick
CONFIG += c++11
TEMPLATE = app

win32 {
    release: DESTDIR = $$OUT_PWD
    debug:   DESTDIR = $$OUT_PWD
}

HEADERS += \
    src/cpp/Utils.h \
    src/cpp/Settings.h \
    src/cpp/Interpreter.h

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/Utils.cpp \
    src/cpp/Settings.cpp \
    src/cpp/Interpreter.cpp

DISTFILES += \
    README.md \
    src/js/utils.js \
    src/js/command.js \
    src/qml/main.qml \
    src/qml/TopMenuBar.qml \
    src/qml/components/filedialog/FileDialogBase.qml \
    src/qml/components/filedialog/FileDialogSave.qml \
    src/qml/components/filedialog/FileDialogOpen.qml \
    src/qml/components/messagedialog/MessageDialogBase.qml \
    src/qml/components/messagedialog/MessageDialogInformation.qml \
    src/qml/components/messagedialog/MessageDialogQuestion.qml \
    src/qml/components/messagedialog/MessageDialogWarning.qml \
    src/qml/components/messagedialog/MessageDialogError.qml \
    src/qml/About.qml \
    src/qml/Options.qml \
    src/qml/WorkArea.qml

RESOURCES += \
    src/greenery.qrc


