QT += qml quick widgets opengl sql

CONFIG += c++11
TEMPLATE = app
TARGET = sproute

lupdate_only {
SOURCES = Source/qml/*.qml \
SOURCES = Source/js/*.js \
    Source/qml/components/*.qml \
    Source/qml/dialogs/*.qml \
    Source/qml/main/*.qml \
    Source/qml/sheets/*.qml \
    Source/qml/units/*.qml \
    Source/qml/windows/*.qml \
}

HEADERS += \
    Source/cpp/Base/Core.h \
    Source/cpp/Base/FileSystemModel.h \
    Source/cpp/Base/OperatorModel.h \
    Source/cpp/Base/OperatorProxyModel.h \
    Source/cpp/Base/Process.h \
    Source/cpp/Base/Settings.h \
    Source/cpp/Db/SproutDb.h \

SOURCES += \
    Source/cpp/Base/Core.cpp \
    Source/cpp/Base/FileSystemModel.cpp \
    Source/cpp/Base/OperatorModel.cpp \
    Source/cpp/Base/OperatorProxyModel.cpp \
    Source/cpp/Base/Process.cpp \
    Source/cpp/Base/Settings.cpp \
    Source/cpp/Db/SproutDb.cpp \
    Source/cpp/main.cpp \

OTHER_FILES += \
    README.md \
    .gitignore \

RESOURCES += \
    Source/qml.qrc \
    Source/js.qrc
