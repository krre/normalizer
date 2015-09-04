import QtQuick 2.5
import QtQuick.Controls 1.4

Rectangle {
    id: root
    property string name
    property string arg
    property bool isCurrent: root === currentNode
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

    Label {
        text: arg
        anchors.centerIn: parent
        color: "white"
    }
}
