.import QtQuick.Dialogs 1.2 as Dialogs
.import "../js/utils.js" as Utils

function infoMessage(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, "qrc:/qml/components/MessageDialogBase.qml",
                                     { icon: Dialogs.StandardIcon.Information, text: message })
}

function warningMessage(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, "qrc:/qml/components/MessageDialogBase.qml",
                                     { icon: Dialogs.StandardIcon.Information, text: message })
}

function questionMessage(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, "qrc:/qml/components/MessageDialogBase.qml",
                                     { icon: Dialogs.StandardIcon.Information, standardButtons: Dialogs.StandardButton.Yes | Dialogs.StandardButton.No, text: message })
}

function errorMessage(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, "qrc:/qml/components/MessageDialogBase.qml",
                                     { icon: Dialogs.StandardIcon.Critical, text: message })
}

