.import QtQuick.Dialogs 1.2 as Dialogs
.import "../js/utils.js" as Utils

var messageDialogUrl = "qrc:/qml/components/MessageDialogBase.qml"

function infoMessage(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, messageDialogUrl,
                                     { icon: Dialogs.StandardIcon.Information, text: message })
}

function warningMessage(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, messageDialogUrl,
                                     { icon: Dialogs.StandardIcon.Information, text: message })
}

function questionMessage(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, messageDialogUrl,
                                     { icon: Dialogs.StandardIcon.Information, standardButtons: Dialogs.StandardButton.Yes | Dialogs.StandardButton.No, text: message })
}

function errorMessage(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, messageDialogUrl,
                                     { icon: Dialogs.StandardIcon.Critical, text: message })
}
