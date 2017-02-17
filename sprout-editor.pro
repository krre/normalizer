QT += qml quick widgets opengl sql

CONFIG += c++11
TEMPLATE = app
TARGET = sproute

include(../qosg/Source/qosg.pri)

LIBS += \
    -L$$(OSG_HOME)/lib \
    -L$$(OSG_HOME)/lib64

CONFIG(debug, debug|release) {
    LIBS += -losgd -losgViewerd -losgGAd -losgDBd -losgUtild -losgTextd -lOpenThreadsd -losgQtd
} else {
    LIBS += -losg -losgViewer -losgGA -losgDB -losgUtil -losgText -lOpenThreads -losgQt
}

INCLUDEPATH += $$(OSG_HOME)/include

lupdate_only {
SOURCES = Source/qml/*.qml \
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
    Source/cpp/Gui/MainWindow.h \
    Source/cpp/Gui/WorkArea.h

SOURCES += \
    Source/cpp/Base/Core.cpp \
    Source/cpp/Base/FileSystemModel.cpp \
    Source/cpp/Base/OperatorModel.cpp \
    Source/cpp/Base/OperatorProxyModel.cpp \
    Source/cpp/Base/Process.cpp \
    Source/cpp/Base/Settings.cpp \
    Source/cpp/Db/SproutDb.cpp \
    Source/cpp/main.cpp \
    Source/cpp/Gui/MainWindow.cpp \
    Source/cpp/Gui/WorkArea.cpp

OTHER_FILES += \
    README.md \
    .gitignore \

RESOURCES += \
    Source/qml.qrc \
    Source/js.qrc
