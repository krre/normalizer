import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import "../../js/command.js" as Command

Rectangle {
    id: root
    property string name
    property string arg
    property bool isCurrent: root === currentNode
    property bool isEdit: isCurrent && commandState === Command.Edit
    property string nodeId
    width: 100
    height: 50
    color: isCurrent ? "darkred" : "green"
    border.color: isCurrent ? "pink" : "lightgreen"
    signal edit(var name)

    MouseArea {
        anchors.fill: parent
        onClicked: currentNode = root
    }

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: name
            color: "white"
            Layout.alignment: Qt.AlignHCenter
        }

        TextEdit {
            visible: isEdit
            Layout.fillWidth: true
            horizontalAlignment: TextEdit.AlignHCenter
            onVisibleChanged: {
                if (visible) {
                    text = arg
                    forceActiveFocus()
                } else if (isCurrent) {
                    arg = text
                    edit(text)
                }
            }
            color: "white"

            Keys.onReturnPressed: commandState = Command.Ready
            Keys.onEnterPressed: commandState = Command.Ready
        }

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: arg
            color: "white"
            visible: !isEdit
        }
    }
}
