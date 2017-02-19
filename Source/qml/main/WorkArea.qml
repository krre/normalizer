import QtQuick 2.8
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

ColumnLayout {
    property alias output: output
    property alias input: input
    spacing: 0

    Component.onCompleted: input.forceActiveFocus()

    TextArea {
        id: output
        Layout.preferredWidth: parent.width
        Layout.fillHeight: true
        style: TextAreaStyle {
            textColor: "white"
            backgroundColor: "black"
        }
    }

    TextField {
        id: input
        Layout.preferredWidth: parent.width
        style: TextFieldStyle {
            textColor: "white"
            background: Rectangle {
                color: "black"
            }
        }
    }
}
