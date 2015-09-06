QT += qml quick widgets sql 3dcore 3drenderer 3dinput 3dquick
CONFIG += c++11
TEMPLATE = app

win32 {
    release: DESTDIR = $$OUT_PWD
    debug:   DESTDIR = $$OUT_PWD
}

win32: LIBS += "-L../sprout/build"
!win32: LIBS += -L../sprout/build

LIBS += -lsproutc -lsproutdb

INCLUDEPATH += ../sprout/sprout-c/src
INCLUDEPATH += ../sprout/sprout-db/src

HEADERS += \
    src/cpp/console.h \
    src/cpp/settings.h \
    src/cpp/sproutdb.h \
    src/cpp/utils.h \
    src/cpp/project.h \
    src/cpp/sproutc.h

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/utils.cpp \
    src/cpp/sproutdb.cpp \
    src/cpp/settings.cpp \
    src/cpp/console.cpp \
    src/cpp/project.cpp \
    src/cpp/sproutc.cpp

DISTFILES += \
    README.md \
    src/js/utils.js \
    src/js/command.js \
    src/js/world.js \
    src/js/dialog.js \
    src/qml/TopMenuBar.qml \
    src/qml/components/filedialog/FileDialogBase.qml \
    src/qml/components/filedialog/FileDialogSave.qml \
    src/qml/components/filedialog/FileDialogOpen.qml \
    src/qml/components/filedialog/FileDialogDirectory.qml \
    src/qml/components/messagedialog/MessageDialogBase.qml \
    src/qml/components/messagedialog/MessageDialogInformation.qml \
    src/qml/components/messagedialog/MessageDialogQuestion.qml \
    src/qml/components/messagedialog/MessageDialogWarning.qml \
    src/qml/components/messagedialog/MessageDialogError.qml \
    src/qml/entities/EntityBase.qml \
    src/qml/entities/Cube.qml \
    src/qml/entities/Sphere.qml \
    src/qml/entities/Text3D.qml \
    src/qml/blocks/Print.qml \
    src/qml/blocks/Project.qml \
    src/qml/sheets/CommandSheet.qml \
    src/qml/About.qml \
    src/qml/Options.qml \
    src/qml/WorkArea.qml \
    src/qml/Output.qml \
    src/qml/main.qml \
    src/qml/NewProject.qml \
    src/qml/blocks/Module.qml \
    src/qml/blocks/Floor.qml \
    src/qml/nodes/NodeBase.qml \
    src/qml/nodes/Project.qml \
    src/qml/nodes/Module.qml \
    src/qml/nodes/Print.qml \
    src/qml/nodes/Function.qml

RESOURCES += \
    src/greenery.qrc \
    src/assets.qrc


