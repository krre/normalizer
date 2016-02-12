import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import "../components"
import "../../js/utils.js" as Utils

WindowDialog {
    id: root
    property string path
    title: qsTr("Rename")
    width: 400
    height: 100

    onAccepted: Utils.renameSprout(path, Core.pathToDir(path) + "/" + name.text)

    GridLayout {
        width: parent.width
        columns: 3

        Label {
            text: qsTr("New name:")
        }

        TextField {
            id: name
            text: Core.pathToFileName(path)
            Layout.fillWidth: true
            Component.onCompleted: {
                cursorPosition = 0
                selectWord()
                forceActiveFocus()
            }
        }
    }
}

