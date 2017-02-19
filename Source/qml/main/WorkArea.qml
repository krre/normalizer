import QtQuick 2.8
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

ColumnLayout {
    property alias output: output
    property alias input: input
    spacing: 0

    Component.onCompleted: input.forceActiveFocus()

    ToolBar {

        RowLayout {
            anchors.fill: parent
            spacing: 0

            ToolButton {
                text: qsTr("Clear Output")
                onClicked: output.clear()
            }

            ToolButton {
                text: qsTr("Clear Input History")
                onClicked: input.clearHistory()
            }
        }
    }

    TextArea {
        id: output
        Layout.preferredWidth: parent.width
        Layout.fillHeight: true
        readOnly: true
        style: TextAreaStyle {
            textColor: "white"
            backgroundColor: "black"
        }

        function clear() {
            cursorPosition = 0
            text = ""
        }
    }

    TextField {
        id: input
        property var history: []
        property int historyPos: 0
        Layout.preferredWidth: parent.width
        style: TextFieldStyle {
            textColor: "white"
            background: Rectangle {
                color: "black"
            }
        }

        function sendCommand() {
            output.append(text)
            history.push(text)
            historyPos = history.length
            text = ""
        }

        function clearHistory() {
            history = []
            historyPos = 0
            text = ""
        }

        Keys.onReturnPressed: sendCommand()
        Keys.onEnterPressed: sendCommand()

        Keys.onUpPressed: {
            if (historyPos - 1 >= 0) {
                text = history[--historyPos]
            }
        }

        Keys.onDownPressed: {
            if (historyPos + 1 < history.length) {
                text = history[++historyPos]
            } else {
                text = ""
            }
        }
    }
}
