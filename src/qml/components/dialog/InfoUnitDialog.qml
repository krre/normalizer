import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import "../../../js/command.js" as Command

DialogBase {
    id: root
    property var unit
    title: qsTr("Info Unit")
    width: 400
    standardButtons: StandardButton.Ok

    onVisibleChanged: commandState = Command.Ready

    GridLayout {
        width: parent.width
        columns: 2
        columnSpacing: 10
        rowSpacing: 10

        Label {
            text: qsTr("Title:")
        }

        TextField {
            text: unit.title
            Layout.fillWidth: true
            readOnly: true
        }

        Label {
            text: qsTr("Type:")
        }

        TextField {
            text: unit.type
            Layout.fillWidth: true
            readOnly: true
        }

        Label {
            text: qsTr("Argument:")
        }

        TextField {
            text: unit.arg
            Layout.fillWidth: true
            readOnly: true
        }
    }
}
