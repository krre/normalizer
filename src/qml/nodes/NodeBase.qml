import QtQuick 2.5
import QtQuick.Controls 1.4

Rectangle {
    property string name
    property string arg
    width: 100
    height: 100
    color: "green"
    border.color: "lightgreen"

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
