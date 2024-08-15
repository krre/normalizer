QT += qml quick widgets opengl sql
QT += 3dcore 3drender 3dinput 3dextras

CONFIG += c++11
TEMPLATE = app
TARGET = sproute

lupdate_only {
SOURCES = Source/qml/*.qml \
SOURCES = Source/js/*.js \
    Source/qml/components/*.qml \
    Source/qml/dialogs/*.qml \
    Source/qml/main/*.qml \
    Source/qml/main/editorspace/*.qml \
    Source/qml/main/toolspace/*.qml \
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
    Source/cpp/UI/MainWindow.h \
    Source/cpp/Defines.h \
    Source/cpp/UI/Editor3D.h \
    Source/cpp/Sprout/SproutManager.h \
    Source/cpp/UI/Options.h \
    Source/cpp/UI/SelectWorkspace.h

SOURCES += \
    Source/cpp/Base/Core.cpp \
    Source/cpp/Base/FileSystemModel.cpp \
    Source/cpp/Base/OperatorModel.cpp \
    Source/cpp/Base/OperatorProxyModel.cpp \
    Source/cpp/Base/Process.cpp \
    Source/cpp/Base/Settings.cpp \
    Source/cpp/Db/SproutDb.cpp \
    Source/cpp/main.cpp \
    Source/cpp/UI/MainWindow.cpp \
    Source/cpp/UI/Editor3D.cpp \
    Source/cpp/Sprout/SproutManager.cpp \
    Source/cpp/UI/Options.cpp \
    Source/cpp/UI/SelectWorkspace.cpp

OTHER_FILES += \
    README.md \
    .gitignore \

RESOURCES += \
    Source/qml.qrc \
    Source/js.qrc

FORMS += \
    Source/cpp/UI/MainWindow.ui \
    Source/cpp/UI/Options.ui \
    Source/cpp/UI/SelectWorkspace.ui
