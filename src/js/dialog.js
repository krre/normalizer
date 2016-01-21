.import "../js/utils.js" as Utils

function infoMessage(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, "qrc:/qml/components/messagedialog/MessageDialogInformation.qml", { text: message })
}

function warningMessage(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, "qrc:/qml/components/messagedialog/MessageDialogWarning.qml", { text: message })
}

function questionMessage(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, "qrc:/qml/components/messagedialog/MessageDialogQuestion.qml", { text: message })
}

function errorMessage(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, "qrc:/qml/components/messagedialog/MessageDialogError.qml", { text: message })
}

