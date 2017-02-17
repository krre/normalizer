QT += qml quick widgets opengl

CONFIG += c++11

TEMPLATE = app
TARGET = sproutr

lupdate_only {
SOURCES = Source/qml/*.qml \
}

SOURCES += \
    Source/cpp/main.cpp

OTHER_FILES += \
    .gitignore \
    README.md

RESOURCES += \
    Source/qml.qrc \
