import QtQuick 2.5
import QtQuick.Controls 1.4
import "../../js/command.js" as Command

Rectangle {
    id: root
    property string name
    property string arg
    property bool isCurrent: root === currentNode
    property bool isEdit: isCurrent && commandState === Command.Edit
    width: 100
    height: 100
    color: isCurrent ? "darkred" : "green"
    border.color: isCurrent ? "pink" : "lightgreen"

    MouseArea {
        anchors.fill: parent
    }

    Label {
        text: name
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        color: "white"
    }

    TextField {
        visible: isEdit
        width: parent.width
        anchors.centerIn: parent
        onVisibleChanged: {
            if (visible) {
                text = arg
                forceActiveFocus()
            } else if (isCurrent) {
                arg = text
            }
        }

        Keys.onReturnPressed: commandState = Command.Ready
        Keys.onEnterPressed: commandState = Command.Ready
    }

    Label {
        text: arg
        anchors.centerIn: parent
        color: "white"
        visible: !isEdit
    }
}
