QT += qml quick widgets
CONFIG += c++11
TEMPLATE = app

win32 {
    release: DESTDIR = $$OUT_PWD
    debug:   DESTDIR = $$OUT_PWD
}

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/utils.cpp \
    src/cpp/settings.cpp \
    src/cpp/interpreter.cpp

DISTFILES += \
    README.md \
    src/js/utils.js \
    src/js/glcode.js \
    src/js/command.js \
    src/js/three.js \
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
    src/qml/AstArea.qml \
    src/qml/Options.qml

RESOURCES += \
    src/greenery.qrc \
    src/three.qrc

HEADERS += \
    src/cpp/utils.h \
    src/cpp/settings.h \
    src/cpp/interpreter.h

