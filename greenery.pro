QT += opengl qml quick sql

CONFIG += c++11
TEMPLATE = app

LIBS += \
    -L$$(SPROUT_HOME)/bin \
    -L$$(OSG_HOME)/lib \
    -L$$(OSG_HOME)/lib64

CONFIG(debug, debug|release) {
    LIBS += -lsproutd -losgd -losgViewerd -losgGAd -losgDBd -losgUtild -losgTextd -lOpenThreadsd
} else {
    LIBS += -lsprout -losg -losgViewer -losgGA -losgDB -losgUtil -losgText -lOpenThreads
}

INCLUDEPATH += \
    $$(SPROUT_HOME)/include \
    $$(OSG_HOME)/include

HEADERS += \
    src/cpp/console.h \
    src/cpp/settings.h \
    src/cpp/utils.h \
    src/cpp/version.h \
    src/cpp/registertypes.h \
    src/cpp/scenegraph/camera.h \
    src/cpp/scenegraph/node.h \
    src/cpp/scenegraph/scene.h \
    src/cpp/scenegraph/viewport.h \
    src/cpp/scenegraph/frame.h \
    src/cpp/scenegraph/geometry.h \
    src/cpp/osgbridge/osgViewer/renderthread.h \
    src/cpp/osgbridge/osgViewer/texturenode.h \
    src/cpp/osgbridge/osgViewer/view.h \
    src/cpp/osgbridge/osgViewer/viewer_thread.h

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/utils.cpp \
    src/cpp/settings.cpp \
    src/cpp/console.cpp \
    src/cpp/scenegraph/camera.cpp \
    src/cpp/scenegraph/node.cpp \
    src/cpp/scenegraph/scene.cpp \
    src/cpp/scenegraph/viewport.cpp \
    src/cpp/scenegraph/frame.cpp \
    src/cpp/scenegraph/geometry.cpp \
    src/cpp/osgbridge/osgViewer/renderthread.cpp \
    src/cpp/osgbridge/osgViewer/texturenode.cpp \
    src/cpp/osgbridge/osgViewer/view.cpp \
    src/cpp/osgbridge/osgViewer/viewer_thread.cpp

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
