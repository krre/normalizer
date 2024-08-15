import QtQuick 2.8
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    property alias title: title.text
    anchors.centerIn: parent
    width: 200
    height: 50
    color: "black"
    opacity: 0.7

    Component.onCompleted: value.forceActiveFocus()

    signal enter(var value)

    states: [
        State {
            name: "function"
            PropertyChanges {
                target: title
                text: qsTr("Function:")
            }
        }
    ]

    Shortcut {
        sequence: "Esc"
        onActivated: root.destroy()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5

        Label {
            id: title
            color: "white"
        }

        TextInput {
            id: value
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "white"

            Keys.onReturnPressed: {
                if (text) {
                    root.enter(text)
                }
            }
        }
    }
}
