import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    width: 200
    property color labelColor: "white"

    Grid {
        anchors.fill: parent
        anchors.margins: 10
        columns: 2
        columnSpacing: 20

        Label {
            text: "a"
            color: labelColor
        }

        Label {
            text: qsTr("Add")
            color: labelColor
        }

        Label {
            text: "e"
            color: labelColor
        }

        Label {
            text: qsTr("Edit")
            color: labelColor
        }

        Label {
            text: "d"
            color: labelColor
        }

        Label {
            text:  qsTr("Delete")
            color: labelColor
        }

        Label {
            text: "g"
            color: labelColor
        }

        Label {
            text: qsTr("Go")
            color: labelColor
        }

        Label {
            text: "i"
            color: labelColor
        }

        Label {
            text: qsTr("Info")
            color: labelColor
        }
    }
}
