import QtQuick 2.5
import "../../../js/utils.js" as Utils

FileDialogBase {
    title: qsTr("Open File")
    onAccepted: Utils.openFile(UTILS.urlToPath(fileUrl))
}

