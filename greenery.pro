QT += opengl qml quick

CONFIG += c++11
TEMPLATE = app

include(../qosg/src/qosg.pri)

HEADERS += \
    src/cpp/settings.h \
    src/cpp/registertypes.h \
    src/cpp/process.h \
    src/cpp/core.h

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/settings.cpp \
    src/cpp/process.cpp \
    src/cpp/core.cpp

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
    src/qml/main/About.qml \
    src/qml/main/Output.qml \
    src/qml/main/WorkArea.qml \
    src/qml/main/MainMenu.qml \
    src/qml/components/WindowDialog.qml \
    src/qml/components/ButtonBase.qml \
    src/qml/dialogs/EditUnit.qml \
    src/qml/dialogs/InfoUnit.qml \
    src/qml/dialogs/NewProject.qml \
    src/qml/dialogs/Options.qml

RESOURCES += \
    src/greenery.qrc \
    src/assets.qrc
