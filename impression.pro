QT += opengl qml quick

CONFIG += c++11
TEMPLATE = app

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/base/core.cpp \
    src/cpp/base/settings.cpp

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
    src/qml/main/WorkArea.qml

HEADERS += \
    src/cpp/base/core.h \
    src/cpp/base/settings.h
