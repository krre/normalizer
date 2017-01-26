QT += qml quick widgets opengl sql

CONFIG += c++11
TEMPLATE = app

include(../qosg/src/qosg.pri)

LIBS += \
    -L$$(OSG_HOME)/lib \
    -L$$(OSG_HOME)/lib64

CONFIG(debug, debug|release) {
    LIBS += -losgd -losgViewerd -losgGAd -losgDBd -losgUtild -losgTextd -lOpenThreadsd -losgQtd
} else {
    LIBS += -losg -losgViewer -losgGA -losgDB -losgUtil -losgText -lOpenThreads -losgQt
}

INCLUDEPATH += $$(OSG_HOME)/include

HEADERS += \
    src/cpp/Base/Core.h \
    src/cpp/Base/FileSystemModel.h \
    src/cpp/Base/OperatorModel.h \
    src/cpp/Base/OperatorProxyModel.h \
    src/cpp/Base/Process.h \
    src/cpp/Base/Settings.h \
    src/cpp/Db/SproutDb.h \
    src/cpp/Gui/MainWindow.h \
    src/cpp/Gui/WorkArea.h

SOURCES += \
    src/cpp/Base/Core.cpp \
    src/cpp/Base/FileSystemModel.cpp \
    src/cpp/Base/OperatorModel.cpp \
    src/cpp/Base/OperatorProxyModel.cpp \
    src/cpp/Base/Process.cpp \
    src/cpp/Base/Settings.cpp \
    src/cpp/Db/SproutDb.cpp \
    src/cpp/main.cpp \
    src/cpp/Gui/MainWindow.cpp \
    src/cpp/Gui/WorkArea.cpp

DISTFILES += \
    README.md

RESOURCES += \
    src/qml.qrc \
    src/js.qrc
