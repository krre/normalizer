import QtQuick 2.15
import QtQuick.Dialogs

MessageDialog {
    buttons: MessageDialog.Ok
    parentWindow: appRoot

    function show(message) {
        text = message
        open()
    }
}
