import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

ColumnLayout {
    id: root
    width: 200
    height: 200
    spacing: 0
    visible: false

    onVisibleChanged: {
        if (visible) {
            finderTextField.forceActiveFocus()
        } else {
            finderTextField.text = ""
            currentTab.forceActiveFocus()
        }
    }

    TextField {
        id: finderTextField
        Layout.preferredWidth: parent.width

        Keys.onReturnPressed: root.visible = false
    }

    TableView {
        Layout.preferredWidth: parent.width
        Layout.fillHeight: true
        alternatingRowColors: false
        headerVisible: false

        TableViewColumn {

        }
    }
}
