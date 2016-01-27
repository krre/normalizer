QT += opengl qml quick

CONFIG += c++11
TEMPLATE = app

SOURCES += \
    src/cpp/main.cpp \

RESOURCES += \
    src/qml.qrc \
    src/js.qrc

DISTFILES += \
    README.md \
    src/js/utils.js \
    src/qml/main.qml \
    src/qml/main/MainMenu.qml
