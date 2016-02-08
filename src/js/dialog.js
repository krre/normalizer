.import QtQuick.Dialogs 1.2 as Dialogs
.import "../js/utils.js" as Utils

function createDialog(text, properties, icon, standardButtons) {
    properties = properties || {}
    properties.text = text
    properties.icon = properties.hasOwnProperty("icon") ? properties.icon : icon
    properties.standardButtons = properties.hasOwnProperty("standardButtons") ? properties.standardButtons : standardButtons || Dialogs.StandardButton.Ok

    return Utils.createDynamicObject(parentWindow, "qrc:/qml/components/MessageDialogBase.qml", properties)
}

function simple(text, properties) {
    return createDialog(text, properties, Dialogs.StandardIcon.NoIcon)
}

function info(text, properties) {
    return createDialog(text, properties,  Dialogs.StandardIcon.Information)
}

function warning(text, properties) {
    return createDialog(text, properties, Dialogs.StandardIcon.Warning)
}

function question(text, properties) {
    return createDialog(text, properties, Dialogs.StandardIcon.Question, Dialogs.StandardButton.Yes | Dialogs.StandardButton.No)
}

function error(text, properties) {
    return createDialog(text, properties, Dialogs.StandardIcon.Critical)
}

function selectFile(properties) {
    return Utils.createDynamicObject(parentWindow, "qrc:/qml/components/filedialog/FileDialogOpen.qml", properties || {})
}

function selectDirectory(properties) {
    return Utils.createDynamicObject(parentWindow, "qrc:/qml/components/filedialog/FileDialogDirectory.qml", properties || {})
}
