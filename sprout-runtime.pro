QT += qml quick widgets opengl

CONFIG += c++11

TEMPLATE = app
TARGET = sproutr

lupdate_only {
SOURCES = Source/qml/*.qml \
}

SOURCES += \
    Source/cpp/main.cpp \
    Source/cpp/Base/Settings.cpp

OTHER_FILES += \
    .gitignore \
    README.md

RESOURCES += \
    Source/qml.qrc \

HEADERS += \
    Source/cpp/Base/Settings.h
