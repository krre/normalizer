import QtQuick 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import "../../../js/command.js" as Command
import "../../../js/world.js" as World

Dialog {
    id: root
    property var unit
    title: qsTr("Edit Unit")
    visible: true
    width: 400
    modality: Qt.ApplicationModal
    standardButtons: StandardButton.Ok | StandardButton.Cancel

    onAccepted: {
        World.editModule(unit.unitId, arg.text)
        unit.arg = arg.text
        commandState = Command.Ready
        root.destroy()
    }
    onRejected: {
        commandState = Command.Ready
        root.destroy()
    }

    GridLayout {
        width: parent.width
        columns: 2
        columnSpacing: 10
        rowSpacing: 10

        Label {
            text: qsTr("Title:")
        }

        Label {
            text: unit.title
        }

        Label {
            text: qsTr("Argument:")
        }

        TextField {
            id: arg
            text: unit.arg
            Layout.fillWidth: true
            Component.onCompleted: forceActiveFocus()
        }
    }
}

