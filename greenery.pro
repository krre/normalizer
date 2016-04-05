QT += widgets opengl sql

CONFIG += c++11
TEMPLATE = app

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
    src/cpp/base/core.h \
    src/cpp/base/settings.h \
    src/cpp/base/operatormodel.h \
    src/cpp/base/operatorproxymodel.h \
    src/cpp/base/filesystemmodel.h \
    src/cpp/base/process.h \
    src/cpp/db/sproutdb.h \
    src/gui/mainwindow.h \
    src/gui/workarea.h

SOURCES += \
    src/cpp/base/core.cpp \
    src/cpp/base/settings.cpp \
    src/cpp/base/operatormodel.cpp \
    src/cpp/base/operatorproxymodel.cpp \
    src/cpp/base/filesystemmodel.cpp \
    src/cpp/base/process.cpp \
    src/cpp/db/sproutdb.cpp \
    src/main.cpp \
    src/gui/mainwindow.cpp \
    src/gui/workarea.cpp

DISTFILES += \
    README.md \
    src/js/command.js \
    src/js/dialog.js \
    src/js/object-factory.js \
    src/js/operators.js \
    src/js/style.js \
    src/js/utils.js \
    src/js/world.js \
    src/qml/components/BrowseButton.qml \
    src/qml/components/ButtonBase.qml \
    src/qml/components/filedialog/FileDialogBase.qml \
    src/qml/components/filedialog/FileDialogDirectory.qml \
    src/qml/components/filedialog/FileDialogOpen.qml \
    src/qml/components/filedialog/FileDialogSave.qml \
    src/qml/components/MessageDialogBase.qml \
    src/qml/components/Panel.qml \
    src/qml/components/WindowDialog.qml \
    src/qml/dialogs/EditUnit.qml \
    src/qml/dialogs/InfoUnit.qml \
    src/qml/main.qml \
    src/qml/main/About.qml \
    src/qml/main/Editor3D.qml \
    src/qml/main/Finder.qml \
    src/qml/main/MainMenu.qml \
    src/qml/main/Output.qml \
    src/qml/main/Workspace.qml \
    src/qml/sheets/CommandSheet.qml \
    src/qml/units/Argument.qml \
    src/qml/units/Function.qml \
    src/qml/units/Instruction.qml \
    src/qml/units/Module.qml \
    src/qml/units/Project.qml \
    src/qml/units/UnitBase.qml \
    src/qml/units/UnitSet.qml \
    src/qml/windows/About.qml \
    src/qml/windows/NewSprout.qml \
    src/qml/windows/Options.qml \
    src/qml/windows/Rename.qml \
    src/qml/windows/SelectWorkspace.qml


RESOURCES += \
    src/qml.qrc \
    src/js.qrc
