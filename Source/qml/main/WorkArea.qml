import QtQuick 2.8
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

ColumnLayout {
    spacing: 0

    Component.onCompleted: input.forceActiveFocus()

    TextArea {
        id: console
        Layout.preferredWidth: parent.width
        Layout.fillHeight: true
    }

    TextField {
        id: input
        Layout.preferredWidth: parent.width
    }
}
