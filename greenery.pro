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
    src/cpp/osgbridge/osgViewer/viewer.h \
    src/cpp/osgbridge/osg/node.h \
    src/cpp/osgbridge/osg/group.h \
    src/cpp/osgbridge/osg/transform.h \
    src/cpp/osgbridge/osg/box.h \
    src/cpp/osgbridge/osg/geode.h \
    src/cpp/osgbridge/osg/shapedrawable.h \
    src/cpp/osgbridge/osg/sphere.h \
    src/cpp/osgbridge/osg/drawable.h \
    src/cpp/osgbridge/osg/object.h \
    src/cpp/osgbridge/osg/shape.h \
    src/cpp/osgbridge/osgText/textbase.h

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/utils.cpp \
    src/cpp/settings.cpp \
    src/cpp/console.cpp \
    src/cpp/osgbridge/osgViewer/viewer.cpp \
    src/cpp/osgbridge/osg/node.cpp \
    src/cpp/osgbridge/osg/group.cpp \
    src/cpp/osgbridge/osg/transform.cpp \
    src/cpp/osgbridge/osg/box.cpp \
    src/cpp/osgbridge/osg/geode.cpp \
    src/cpp/osgbridge/osg/shapedrawable.cpp \
    src/cpp/osgbridge/osg/sphere.cpp \
    src/cpp/osgbridge/osg/drawable.cpp \
    src/cpp/osgbridge/osg/object.cpp \
    src/cpp/osgbridge/osg/shape.cpp \
    src/cpp/osgbridge/osgText/textbase.cpp

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
