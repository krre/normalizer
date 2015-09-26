QT += opengl qml quick sql

CONFIG += c++11
TEMPLATE = app

LIBS += \
    -L$$(SPROUT_HOME)/bin \
    -L$$(OSG_HOME)/lib

Debug:LIBS += -lsproutd -losgd -losgViewerd -losgGAd -losgDBd -losgUtild -losgTextd
Release:LIBS += -lsprout -losg -losgViewer -losgGA -losgDB -losgUtil -losgText

INCLUDEPATH += \
    $$(SPROUT_HOME)/include \
    $$(OSG_HOME)/include

HEADERS += \
    src/cpp/console.h \
    src/cpp/settings.h \
    src/cpp/utils.h \
    src/cpp/version.h \
    src/cpp/registertypes.h \
    src/cpp/osg-adapter/scene.h \
    src/cpp/osg-adapter/camera.h \
    src/cpp/osg-adapter/node.h \
    src/cpp/osg-adapter/osgViewer/viewer.h \
    src/cpp/osg-adapter/osgViewer/view.h

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/utils.cpp \
    src/cpp/settings.cpp \
    src/cpp/console.cpp \
    src/cpp/osg-adapter/scene.cpp \
    src/cpp/osg-adapter/camera.cpp \
    src/cpp/osg-adapter/node.cpp \
    src/cpp/osg-adapter/osgViewer/viewer.cpp \
    src/cpp/osg-adapter/osgViewer/view.cpp

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
    src/qml/sheets/CommandSheet.qml \
    src/qml/About.qml \
    src/qml/Options.qml \
    src/qml/WorkArea.qml \
    src/qml/Output.qml \
    src/qml/main.qml \
    src/qml/NewProject.qml \
    src/qml/nodes/NodeBase.qml \
    src/qml/nodes/Project.qml \
    src/qml/nodes/Module.qml \
    src/qml/nodes/Function.qml \
    src/qml/nodes/Argument.qml \
    src/qml/nodes/Instruction.qml

RESOURCES += \
    src/greenery.qrc \
    src/assets.qrc
