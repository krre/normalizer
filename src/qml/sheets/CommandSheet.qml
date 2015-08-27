import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    width: 200
    property color labelColor: "white"

    Column {
        anchors.fill: parent
        anchors.margins: 10

        Label {
            text: "a | Add"
            color: labelColor
        }

        Label {
            text: "e | Edit"
            color: labelColor
        }

        Label {
            text: "d | Delete"
            color: labelColor
        }
    }
}
