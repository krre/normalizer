QT += opengl qml quick sql

CONFIG += c++11
TEMPLATE = app

LIBS += \
    -L$$(SPROUT_HOME)/bin \

CONFIG(debug, debug|release) {
    LIBS += -lsproutd
} else {
    LIBS += -lsprout
}

INCLUDEPATH += \
    $$(SPROUT_HOME)/include \

include(../qosg/qosg.pri)

HEADERS += \
    src/cpp/settings.h \
    src/cpp/utils.h \
    src/cpp/version.h \
    src/cpp/registertypes.h \
    src/cpp/process.h

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/utils.cpp \
    src/cpp/settings.cpp \
    src/cpp/process.cpp

DISTFILES += \
    README.md \
    src/js/utils.js \
    src/js/command.js \
    src/js/world.js \
    src/js/dialog.js \
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
    src/qml/main.qml \
    src/qml/units/Project.qml \
    src/qml/units/Module.qml \
    src/qml/units/Function.qml \
    src/qml/units/Argument.qml \
    src/qml/units/Instruction.qml \
    src/qml/units/UnitBase.qml \
    src/qml/units/UnitSet.qml \
    src/qml/components/dialog/EditUnitDialog.qml \
    src/qml/components/dialog/DialogBase.qml \
    src/qml/components/dialog/NewProjectDialog.qml \
    src/qml/components/dialog/InfoUnitDialog.qml \
    src/qml/main/Options.qml \
    src/qml/main/About.qml \
    src/qml/main/Output.qml \
    src/qml/main/TopMenuBar.qml \
    src/qml/main/WorkArea.qml

RESOURCES += \
    src/greenery.qrc \
    src/assets.qrc
